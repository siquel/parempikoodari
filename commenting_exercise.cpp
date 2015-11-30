// executes perl function with given arguments
static int execute_perl(SV* func, char* args) {
	int count, ret_value = 1;
	// initialize stack pointer
	dSP;
	// enter the stack
	ENTER;
	// everything is temp variable
	SAVETMPS;

	PUSHMARK (SP);
	// push the arguments to stack
	XPUSHs (sv_2mortal (newSVpv (args, 0)));
	// make SP local
	PUTBACK;

	// call the function
	count = call_sv (func, G_EVAL | G_SCALAR);
	// refresh stack pointer
	SPAGAIN;
	// was there errors?
	if (SvTRUE (ERRSV)) {
		printf("Perl error: %s\n", SvPV_nolen (ERRSV));
		// remove undef from the top of the stack 
		if (!SvOK (POPs)) {
			// TODO
		}	
		// did the func return more than 1 variable?	
	} else if (count != 1) {
		printf ("Perl error: expected 1 value from %s, "
						  "got: %d\n", SvPV_nolen (func), count);
	} else {
		// get the return value
		ret_value = static_cast<int>(POPi);
	}
	// refresh
	PUTBACK;
	// free the return value
	FREETMPS;
	// free the XPUSHed variable
	LEAVE;
	return ret_value;
}

namespace uskomaton {
	namespace scripting {
		// uses perl to unload script from memory
		void PerlScriptingAPI::unload(Script* script) {
			// perl wants c style strings, so get the string first
			const char* cfile = script->getFilename().c_str();
			// dirty hack to remove constness
			char file[255];
			strcpy(file, cfile);
			// call the unload function defined in Uskomaton.pm
			// and pass the filename as argument
			execute_perl(sv_2mortal(newSVpv("Uskomaton::unload", 0)), file);
			// free the memory and remove the script
			loadedScripts.erase(std::find(loadedScripts.begin(), loadedScripts.end(), script));
			delete s;
		}
	}
}