#include "Fixture.h"

CommandLineExcecutor Fixture::executor {};

std::string Fixture::text {"By and by, when we got up, we turned over the truck "
                           "the gang had stole off of the wreck, and found boots, "
                           "and blankets, and clothes, and all sorts of other things, "
                           "and a lot of books, and a spyglass, and three boxes of seegars. "
                           "We hadn't ever been this rich before in neither of our lives. "
                           "The seegars was prime. We laid off all the afternoon "
                           "in the woods talking, and me reading the books, and "
                           "having a general good time. I told Jim all about what "
                           "happened inside the wreck and at the ferryboat, "
                           "and I said these kinds of things was adventures; "
                           "but he said he didn't want no more adventures. "
                           "He said that when I went in the texas and he "
                           "crawled back to get on the raft and found her "
                           "gone he nearly died, because he judged it was "
                           "all up with HIM anyway it could be fixed."
                           "Проснувшись, мы пересмотрели все добро, награбленное "
                           "шайкой на разбитом пароходе; там оказались и сапоги, "
                           "и одеяла, и платья, и всякие другие вещи, а еще много книг, "
                           "подзорная труба и три ящика сигар. Такими богачами мы с "
                           "Джимом еще никогда в жизни не были. Сигары оказались "
                           "первый сорт. До вечера мы валялись в лесу и разговаривали; "
                           "я читал книжки; и вообще мы недурно провели время."
                           " Я рассказал Джиму обо всем, что произошло на пароходе "
                           "и на пароме, и сообщил ему кстати, что это и называется приключением"};

boost::program_options::options_description Fixture::desc = boost::program_options::options_description();
