#ifndef MOD_GAME
	#define MOD_GAME
	class ClassGame {
		private:
			long Game_Score;
		protected:
			ClassPeca PECA_PRI;
			ClassTabuleiro TABULEIRO_PRI;
			ClassMetronomy TEMPO;
		public:
			bool Game_Play;
			bool Game_Pause;
			
			ClassGame();
			
			void Events();
			bool Mover_Peca (int i);
			bool Rotacionar_Peca_Check ();
			int Descer_Peca ();
		friend class ClassCurses;
	};
#endif
