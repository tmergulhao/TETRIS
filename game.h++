#ifndef MOD_GAME
	#define MOD_GAME
	class ClassGame {
		private:
			long Game_Score;
		protected:
			ClassPeca PECA_PRI;
			ClassTabuleiro TABULEIRO_PRI;
		public:
			ClassGame();
			
			void Mover_Peca (int i);
			void Rotacionar_Peca_Check ();
			int Descer_Peca ();
		friend class ClassCurses;
	};
#endif
