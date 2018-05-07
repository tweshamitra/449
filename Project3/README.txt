For this project, I wrote a test case aside from the ones provided to do some simple testing.
This project was definitely really tough for me and I tried to implement as much as I could.
I know that my code is allocating space which you can see if you run my test or even in the drivers.
The good thing is that the drivers don't crash due to any runtime errors. However, I'm not entirely sure
why the output doesn't match exactly. I think my free() method is not working properly and I had a tough time
figuring out how to coalesce free blocks. I tried to figure it out over a few days, but I couldn't and couldn't
even get my code to compile or crash. So, at the risk of losing points, I made the choice to forego that
so that my program would compile and run. Given more time, I could definitely implement this better, but
since I had a few other projects due around the same time, that made it tough.

Also, to compile and run, run the following commands:

1. gcc mymalloc.c mallocdrv.c -o mallocdrv
2. ./mallocdrv
