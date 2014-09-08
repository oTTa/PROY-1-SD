struct entrada{
  unsigned long datos1[256];
  unsigned long datos2[256];
};

struct salida {
  unsigned long datos[512];
};

program ej3b1 {
	version ej3b1v1 {
		salida ejecutartarea(entrada) = 1;
	} = 1;
} = 0x20000001;