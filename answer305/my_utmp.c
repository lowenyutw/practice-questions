#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utmpx.h>

#define UT_LINESIZE 32
#define UT_NAMESIZE 32
#define UT_HOSTSIZE 256

struct my_utmpx
{
    short ut_type;
    char ut_line[UT_LINESIZE];
    char ut_user[UT_NAMESIZE];
    char ut_host[UT_HOSTSIZE];

#if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
    struct
    {
        int32_t tv_sec;  
        int32_t tv_usec; 
    } ut_tv;             
#else
    struct timeval ut_tv; 
#endif
};

struct utmpxlist
{
    struct my_utmpx u;
    struct utmpxlist *next;
};

int main(void)
{
    struct utmpxlist *ulp, *ulprev, *reful = NULL, *ulhead = NULL;
    struct utmpx *rulp;

    while (1)
    {
        while (1)
        {
            ulp = calloc(1, sizeof(struct utmpxlist));

            if (ulp == NULL)
            {
                perror("calloc");
                exit(-1);
            }

            if ((rulp = getutxent()) == NULL)
            {
                free(ulp);
                break;
            }
            
            strcpy(ulp->u.ut_host, rulp->ut_host);
            strcpy(ulp->u.ut_line, rulp->ut_line);
            ulp->u.ut_tv.tv_sec = rulp->ut_tv.tv_sec;
            ulp->u.ut_type = rulp->ut_type;
            strcpy(ulp->u.ut_user, rulp->ut_user);

            if (ulhead == NULL)
            {
                ulhead = ulp;
            }
            else
            {
                ulprev->next = ulp;
            }

            ulprev = ulp;
        }

        if (reful != NULL)
        {
            struct utmpxlist *tmpul = reful;
            struct utmpxlist *refulprev = NULL;
            time_t now = time(0);
            int timep = 1;
            while (1)
            {
                if (tmpul->u.ut_tv.tv_sec == ulhead->u.ut_tv.tv_sec)
                {
                    if (tmpul->next == NULL && ulhead->next == NULL)
                    {
                        free(ulhead);
                        break;
                    }

                    if (tmpul->next != NULL)
                    {
                        refulprev = tmpul;
                        tmpul = tmpul->next;
                    }

                    if (ulhead->next != NULL)
                    {
                        ulprev = ulhead;
                        ulhead = ulhead->next;
                        free(ulprev);
                    }
                }
                else
                {
                    time_t tmpult = tmpul->u.ut_tv.tv_sec;
                    time_t ulheadt = ulhead->u.ut_tv.tv_sec;

                    if (tmpul->next == NULL && ulhead->next == NULL)
                    {
                        if (tmpul->u.ut_type != DEAD_PROCESS || ulhead->u.ut_type != DEAD_PROCESS)
                        {
                            if (timep)
                            {
                                printf("%s", ctime(&now));
                                timep = 0;
                            }

                            if (ulhead->u.ut_type != DEAD_PROCESS)
                            {
                                printf("Added:\n%8.8s|%16.16s|%8.8s|%s",
                                       ulhead->u.ut_user, ulhead->u.ut_host,
                                       ulhead->u.ut_line, ctime(&ulheadt));
                            }

                            if (tmpul->u.ut_type != DEAD_PROCESS)
                            {
                                printf("Removed:\n%8.8s|%16.16s|%8.8s|%s",
                                       tmpul->u.ut_user, tmpul->u.ut_host,
                                       tmpul->u.ut_line, ctime(&tmpult));
                            }
                        }

                        if (refulprev != NULL)
                        {
                            refulprev->next = ulhead;
                        }
                        ulprev = tmpul;
                        tmpul = ulhead;
                        free(ulprev);
                        break;
                    }

                    if (tmpul->next != NULL)
                    {
                        if (tmpul->u.ut_type != DEAD_PROCESS)
                        {
                            if (timep)
                            {
                                printf("%s", ctime(&now));
                                timep = 0;
                            }
                            printf("Removed:\n%8.8s|%16.16s|%8.8s|%s",
                                   tmpul->u.ut_user, tmpul->u.ut_host,
                                   tmpul->u.ut_line, ctime(&tmpult));
                        }

                        if (refulprev != NULL)
                        {
                            refulprev->next = tmpul->next;
                        }
                        ulprev = tmpul;
                        tmpul = tmpul->next;
                        free(ulprev);
                    }
                    else
                    {
                        tmpul->next = ulhead;

                        while (1)
                        {
                            if (ulhead->u.ut_type != DEAD_PROCESS)
                            {
                                if (timep)
                                {
                                    printf("%s", ctime(&now));
                                    timep = 0;
                                }
                                printf("Added:\n%8.8s|%16.16s|%8.8s|%s",
                                       ulhead->u.ut_user, ulhead->u.ut_host,
                                       ulhead->u.ut_line, ctime(&ulheadt));
                            }

                            if (ulhead->next == NULL)
                            {
                                break;
                            }

                            ulhead = ulhead->next;
                        }

                        break;
                    }
                }
            }
            if (!timep)
            {
                printf("\n");
            }

            ulhead = reful;
        }
        else
        {
            reful = ulhead;
        }

        ulhead = NULL;
        sleep(5);
        setutxent();
    }
    return 0;
}