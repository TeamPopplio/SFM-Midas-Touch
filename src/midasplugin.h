/**
 * Midas Touch
 * Copyright (c) 2022 KiwifruitDev
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_
#define _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_

#include "engine_wrappers.h"

#if defined WIN32 && !defined snprintf
#define snprintf _snprintf
#endif

class MidasTouch : public ISmmPlugin, public IMetamodListener
{
public:
	bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late);
	bool Unload(char *error, size_t maxlen);
	bool Pause(char *error, size_t maxlen);
	bool Unpause(char *error, size_t maxlen);
	void AllPluginsLoaded();
public: //IMetamodListener stuff
	void OnVSPListening(IServerPluginCallbacks *iface);
public: //hooks
	void Hook_ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);
	bool Hook_LevelInit(const char *pMapName,
		char const *pMapEntities,
		char const *pOldLevel,
		char const *pLandmarkName,
		bool loadGame,
		bool background);
	void Hook_GameFrame(bool simulating);
	void Hook_LevelShutdown(void);
	void Hook_ClientActive(edict_t *pEntity, bool bLoadGame);
	void Hook_ClientDisconnect(edict_t *pEntity);
	void Hook_ClientPutInServer(edict_t *pEntity, char const *playername);
	void Hook_SetCommandClient(int index);
	void Hook_ClientSettingsChanged(edict_t *pEdict);
	bool Hook_ClientConnect(edict_t *pEntity, 
		const char *pszName,
		const char *pszAddress,
		char *reject,
		int maxrejectlen);
#if SOURCE_ENGINE >= SE_ORANGEBOX
	void Hook_ClientCommand(edict_t *pEntity, const CCommand &args);
#else
	void Hook_ClientCommand(edict_t *pEntity);
#endif
public:
	const char *GetAuthor();
	const char *GetName();
	const char *GetDescription();
	const char *GetURL();
	const char *GetLicense();
	const char *GetVersion();
	const char *GetDate();
	const char *GetLogTag();
};

extern MidasTouch g_MidasTouch;

PLUGIN_GLOBALVARS();

#endif //_INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_
