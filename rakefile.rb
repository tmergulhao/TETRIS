TOPFLAGS = ""
DFLAGS = ""

task :default_before do
	TOPFLAGS << "-lSDL2 -lSDL2_image "
end
task :default => [:default_before, 'main.o', :link, :run, :clean]

task :ncurses_before do
	DFLAGS << "-DNCURSES "
	TOPFLAGS << "-lncurses "
end
task :ncurses => [:ncurses_before, 'main.curses.o', :link, :run, :clean]

task :test_before do
	DFLAGS << "-fprofile-arcs " << "-ftest-coverage "
	TOPFLAGS = "-lcunit "
end
task :test => [:test_before,'main.test.o', :link, :run, :cover, :clean]


rule '.o'  => '.c++' do |t|
	sh "g++ -c #{DFLAGS} #{t.source}"
end
task :link do
	sh "g++ *.o #{TOPFLAGS}#{DFLAGS}-o compiled.out"
end
task :run do
	sh "./compiled.out"
end
task :cover do
	sh "gcov *.o"
end
task :clean do
	sh "rm *.o *.out *.gcov *.gcda *.gcno"
end

file 'main.o' => ['main.c++', 'main.h++', 'game.o', 'peca.o', 'tabuleiro.o', 'metronomo.o', 'textures.o']
file 'main.curses.o' => ['main.curses.c++', 'main.h++', 'game.o', 'peca.o', 'tabuleiro.o', 'metronomo.o']
file 'main.test.o' => ['main.test.c++', 'main.h++', 'game.o', 'peca.o', 'tabuleiro.o', 'metronomo.o']

file 'game.o' => ['main.h++', 'game.h++', 'game.c++']
file 'peca.o' => ['main.h++', 'peca.h++', 'peca.c++']
file 'tabuleiro.o' => ['main.h++', 'tabuleiro.h++', 'tabuleiro.c++']

file 'metronomo.o' => ['metronomo.h++', 'metronomo.c++']
