#ifndef MOD_PECA
	#define MOD_PECA

	#ifdef SERVIDOR_PECA
		#define EXT_MOD_PECA
	#else
		#define EXT_MOD_PECA extern
	#endif
	
	class ClassPeca {
		public:
			int X, Y;
			struct {
				int X, Y;
			} BLOCO[4];
			
			void Set(int j, int i);
			
			void Rotacionar_Peca ();
			void Iniciar_Peca (int i);
			
			int CoordX (int i) {	return (X + BLOCO[i].X);	}
			int CoordY (int i) {	return (Y + BLOCO[i].Y);	}
			
			ClassPeca operator = (ClassPeca);
	};

#endif