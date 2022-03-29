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

#ifndef _INCLUDE_SOURCE_ENGINE_WRAPPERS_
#define _INCLUDE_SOURCE_ENGINE_WRAPPERS_

#include <eiface.h>

extern IVEngineServer *engine;
extern CGlobalVars *gpGlobals;

#define ENGINE_CALL(func) SH_CALL(engine, &IVEngineServer::func)

#define MM_Format g_SMAPI->Format

inline int IndexOfEdict(const edict_t *pEdict)
{
	return (int)(pEdict - gpGlobals->pEdicts);
}
inline edict_t *PEntityOfEntIndex(int iEntIndex)
{
	if (iEntIndex >= 0 && iEntIndex < gpGlobals->maxEntities)
	{
		return (edict_t *)(gpGlobals->pEdicts + iEntIndex);
	}
	return NULL;
}

#endif //_INCLUDE_SOURCE_ENGINE_WRAPPERS_
