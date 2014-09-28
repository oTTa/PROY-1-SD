struct tiempo {
         unsigned long seconds;
         unsigned long useconds;
     };
     
program ej7 {
	version ej7v1 {
		tiempo horaSistema() = 1;
	} = 1;
} = 0x20000001; 
