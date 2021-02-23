#include "stdafx.h"

//#include <wchar.h>
//#include "Parm.h"
//#include "Error.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[]) {
		PARM parms;
		bool check_in = false;
		bool check_out = false;
		bool check_log = false;
		int num_parm;
		_TCHAR* firstSymbol;
		for (num_parm = 1; num_parm < argc; num_parm++) {
			if (wcslen(argv[num_parm]) > PARM_MAX_SIZE) throw ERROR_THROW(104);
			firstSymbol = &argv[num_parm][0];
			if (wcsstr(argv[num_parm], PARM_IN) == firstSymbol) {
				check_in = true;
				wcscpy_s(parms.in, argv[num_parm] + wcslen(PARM_IN));
			}
			else if (wcsstr(argv[num_parm], PARM_OUT) == firstSymbol) {
				check_out = true;
				wcscpy_s(parms.out, argv[num_parm] + wcslen(PARM_OUT));
			}
			else if (wcsstr(argv[num_parm], PARM_LOG) == firstSymbol) {
				check_log = true;
				wcscpy_s(parms.log, argv[num_parm] + wcslen(PARM_LOG));
			}
		}
		if (!check_in) throw ERROR_THROW(100);
		if (!check_out) {
			wcscpy_s(parms.out, parms.in);
			wcscat_s(parms.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!check_log) {
			wcscpy_s(parms.log, parms.in);
			wcscat_s(parms.log, PARM_LOG_DEFAULT_EXT);
		}
		return parms;
	}
}