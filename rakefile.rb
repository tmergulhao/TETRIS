OBJECTS = ['game.o', 'peca.o', 'tabuleiro.o', 'metronomo.o']
TOPFLAGS = "-lncurses"
DFLAGS = ""
MAINOBJ = 'main.o'
DFLAGS << "-DNDEBUG "

task :default => ['main.o','compiled.out'] do
	sh "read null"
	sh "./compiled.out"
	
	Rake::Task[:clean].invoke
end

task :test_set do
	DFLAGS << "-fprofile-arcs " << "-ftest-coverage "
	TOPFLAGS = "-lcunit "
end
task :test => [:test_set,'main.test.o','compiled.out'] do
	sh "./compiled.out"
	sh "read null"
	sh "gcov peca.o tabuleiro.o metronomo.o"
	
	Rake::Task[:clean].invoke
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
file 'main.o' => ['main.test.c++', 'main.h++', 'game.h++', 'peca.h++', 'tabuleiro.h++', 'metronomo.h++']
file 'game.o' => ['main.h++', 'game.h++', 'game.c++']
file 'peca.o' => ['main.h++', 'peca.h++', 'peca.c++']
file 'tabuleiro.o' => ['main.h++', 'tabuleiro.h++', 'tabuleiro.c++']
file 'metronomo.o' => ['metronomo.h++', 'metronomo.c++']
