
/*======================================================================*/
/*																		*/
/*								GSMLIB.H								*/
/*																		*/
/*======================================================================*/

/*
Initialize GSM
	Input
		line
			line for displaying process bar
	
	Return value
		 0: GSM module is OK
		-1: GSM module does not answer for ATE0 command
		-2: GSM module does not answer for AT commands
		-3: unknown GSM module
		-4: GSM module returns ERROR for AT commands
*/
extern int GprsWavecomInitialization(char line);
extern int GprsCinterionInitialization(char line);

/* */
