OBJECTS = ['game.o', 'peca.o', 'tabuleiro.o', 'metronomo.o']
TOPFLAGS = ""
DFLAGS = ""

task :default_before do
	TOPFLAGS << "-lSDL2 -lSDL2_image "
end
task :default => [:default_before, 'main.o','compiled.out'] do
	sh "read null"
	sh "./compiled.out"
end

task :ncurses_before do
	DFLAGS << "-DNCURSES "
	TOPFLAGS << "-lncurses "
end
task :ncurses => [:ncurses_before, 'main.curses.o', 'compiled.out'] do
	sh "read null"
	sh "./compiled.out"
end

task :test_before do
	DFLAGS << "-fprofile-arcs " << "-ftest-coverage "
	TOPFLAGS = "-lcunit "
end
task :test => [:test_before,'main.test.o','compiled.out'] do
	sh "read null"
	sh "./compiled.out"
	sh "gcov peca.o tabuleiro.o metronomo.o"
end

task :clean do
	sh "rm *.o *.out *.gcov *.gcda *.gcno"
end

rule '.o' => '.c++' do |t|
	sh "g++ -c #{DFLAGS} #{t.source}"
end

file 'compiled.out' => OBJECTS do
	sh "g++ *.o #{TOPFLAGS} #{DFLAGS} -o compiled.out"
end

file 'main.test.o' => ['main.test.c++', 'main.h++', 'game.h++', 'peca.h++', 'tabuleiro.h++', 'metronomo.h++']
file 'main.curses.o' => ['main.curses.c++', 'main.h++', 'game.h++', 'peca.h++', 'tabuleiro.h++', 'metronomo.h++']
file 'main.o' => ['main.test.c++', 'main.h++', 'game.h++', 'peca.h++', 'tabuleiro.h++', 'metronomo.h++']
file 'game.o' => ['main.h++', 'game.h++', 'game.c++']
file 'peca.o' => ['main.h++', 'peca.h++', 'peca.c++']
file 'tabuleiro.o' => ['main.h++', 'tabuleiro.h++', 'tabuleiro.c++']
file 'metronomo.o' => ['metronomo.h++', 'metronomo.c++']
