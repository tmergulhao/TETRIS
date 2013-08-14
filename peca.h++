#ifndef MOD_PECA
	#define MOD_PECA
	
	class ClassPeca {
		public:
			int X, Y;
			struct {
				int X, Y;
			} BLOCO[4];
			
			void Rotacionar_Peca ();
			void Iniciar_Peca (int i);
			
			int CoordX (int i) {	return (X + BLOCO[i].X);	}
			int CoordY (int i) {	return (Y + BLOCO[i].Y);	}
			
			void operator = (ClassPeca);
	};
#endif
