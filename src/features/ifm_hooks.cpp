#include "stdafx.hpp"
#include "..\feature.hpp"
#include <QtCore>
#include <QtGui>
#include <QMetaObject>
#include <tier0/dbg.h>

typedef void* (__fastcall* _MainWindowInteracted)(void* thisptr, int edx);
typedef void (__fastcall* _PaintViewport)(void* thisptr, int edx);

// Test for SFM functionality.
class IFMHooks : public FeatureWrapper<IFMHooks>
{
public:
	static void* __fastcall HOOKED_CMovieDocOnDataChanged(void* thisptr, int edx);
	static void __fastcall HOOKED_PaintViewport(void* thisptr, int edx);

	// Modal flags:
	// 1 - Welcome screen.
	// 2 - Animation set editor not found.
	// 4 - Viewport not found.
	int AcknowledgedModalFlags;

	QWidget* MainWindow;
	QWidget* AnimationSetEditor;
	QWidget* Viewport;

protected:
	_MainWindowInteracted ORIG_CMovieDocOnDataChanged = nullptr;
	_PaintViewport ORIG_PaintViewport = nullptr;

	virtual bool ShouldLoadFeature() override
	{
		return true;
	}

	virtual void InitHooks() override
	{
		HOOK_FUNCTION(ifm, CMovieDocOnDataChanged);
		HOOK_FUNCTION(ifm, PaintViewport);
	}

	virtual void LoadFeature() override
	{
		Msg("Midas Touch: ifm.dll hooks initialized.\n");
	}

	virtual void UnloadFeature() override
	{

	}
};

static IFMHooks sfm_test;

void* __fastcall IFMHooks::HOOKED_CMovieDocOnDataChanged(void* thisptr, int edx)
{
	if (sfm_test.MainWindow == nullptr)
	{
		foreach(QWidget * widget, qApp->topLevelWidgets())
		{
			if (widget->inherits("QMainWindow"))
			{
				sfm_test.MainWindow = widget;
				//Msg("Midas Touch: Found main window.\n");
				break;
			}
		}
	}
	if (sfm_test.MainWindow != nullptr)
	{
		// Replace title of SFM.
		QString windowTitle = sfm_test.MainWindow->windowTitle();
		QString replaceString = QString::fromAscii("Source Filmmaker [Beta]");
		QString afterString = QString::fromAscii("SFM: Midas Touch");
		sfm_test.MainWindow->setWindowTitle(windowTitle.replace(replaceString, afterString));
		if ((sfm_test.AcknowledgedModalFlags & 1) == 0)
		{
			// Show welcome modal.
			sfm_test.AcknowledgedModalFlags = 1 | sfm_test.AcknowledgedModalFlags;
			QMessageBox messageBox;
			messageBox.information(0, "Midas Touch: Welcome", "Midas Touch has loaded and hooked into SFM successfully.\n\nPlease report any issues to:\nhttps://github.com/TeamPopplio/SFM-Midas-Touch/issues\n\nHappy editing!");
		}
		// Find animation set editor.
		if (sfm_test.AnimationSetEditor == nullptr)
		{
			QWidget* widget = sfm_test.MainWindow->findChild<QWidget*>(QString::fromAscii("QAnimationSetEditor"));
			if (widget != nullptr)
			{
				Msg("Midas Touch: Found the animation set editor.\n");
				sfm_test.AnimationSetEditor = widget;
			}
			else if ((sfm_test.AcknowledgedModalFlags & 2) == 0)
			{
				Error("Midas Touch: Failed to find the animation set editor.\n");
				// Show error modal.
				sfm_test.AcknowledgedModalFlags = 2 | sfm_test.AcknowledgedModalFlags;
				QMessageBox messageBox;
				messageBox.critical(0, "Midas Touch: Error", "Could not find the animation set editor widget!\nMidas Touch may not function correctly.\nPlease open the animation set editor widget.");
			}
		}
		// Find viewport.
		if (sfm_test.Viewport == nullptr)
		{
			QWidget* widget = sfm_test.MainWindow->findChild<QWidget*>(QString::fromAscii("QViewportArea"));
			if (widget != nullptr)
			{
				Msg("Midas Touch: Found the viewport.\n");
				sfm_test.Viewport = widget;
			}
			else if ((sfm_test.AcknowledgedModalFlags & 4) == 0)
			{
				Error("Midas Touch: Failed to find the viewport.\n");
				// Show error modal.
				sfm_test.AcknowledgedModalFlags = 4 | sfm_test.AcknowledgedModalFlags;
				QMessageBox messageBox;
				messageBox.critical(0, "Midas Touch: Error", "Could not find the viewport widget!\nMidas Touch may not function correctly.\nPlease open the viewport widget.");
			}
		}
	}
	return sfm_test.ORIG_CMovieDocOnDataChanged(thisptr, edx);
}

void __fastcall IFMHooks::HOOKED_PaintViewport(void* thisptr, int edx)
{
	sfm_test.ORIG_PaintViewport(thisptr, edx);
}

QWidget* GetMainWindow()
{
	return sfm_test.MainWindow;
}

QWidget* GetAnimationSetEditor()
{
	return sfm_test.AnimationSetEditor;
}
