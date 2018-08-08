#include "mark_log/mark_log.h"
#include <unistd.h>
#include <string.h>

int main()
{
    int num = 0;
    char buf[12];
    strcpy(buf, "hello world");
    mark_create();

    while(num < 10)
    {
        MARK_LOG(MARK_DEBUG, "The key is %s\n", buf);
        sleep(2);
        num++;
    }
    mark_clean();
    return 0;
}
