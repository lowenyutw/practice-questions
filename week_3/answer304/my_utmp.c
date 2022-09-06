#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utmpx.h>
struct utmpxlist
{
    struct utmpx u;
    struct utmpxlist *next;
};

int main(void)
{
    struct utmpxlist *ulp, *ulprev, *reful = NULL, *ulhead = NULL;
    struct utmpx *rulp;

    while (1)
    {
        //printf("------ulp start------\n");
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
            ulp->u = *rulp;

            if (ulhead == NULL)
            {
                ulhead = ulp;
            }
            else
            {
                ulprev->next = ulp;
            }

            // if (ulp->u.ut_type != DEAD_PROCESS)
            // {
            //     time_t t = ulp->u.ut_tv.tv_sec;
            //     printf("%8.8s|%16.16s|%8.8s|%s", ulp->u.ut_user,
            //            ulp->u.ut_host, ulp->u.ut_line, ctime(&t));
            // }

            ulprev = ulp;
        }
        //printf("------ulp end------\n");

        if (reful != NULL)
        {
            struct utmpxlist *tmpul = reful;
            struct utmpxlist *refulprev = NULL;
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
                    time_t now = time(0);
                    time_t tmpult = tmpul->u.ut_tv.tv_sec;
                    time_t ulheadt = ulhead->u.ut_tv.tv_sec;

                    if (tmpul->next == NULL && ulhead->next == NULL)
                    {
                        if (tmpul->u.ut_type != DEAD_PROCESS || ulhead->u.ut_type != DEAD_PROCESS)
                        {
                            printf("%s", ctime(&now));

                            if (ulhead->u.ut_type != DEAD_PROCESS)
                            {
                                printf("Added:\n%8.8s|%16.16s|%8.8s|%s",
                                       ulhead->u.ut_user, ulhead->u.ut_host,
                                       ulhead->u.ut_line, ctime(&ulheadt));
                            }

                            if (tmpul->u.ut_type != DEAD_PROCESS)
                            {
                                printf("%sRemoved:\n%8.8s|%16.16s|%8.8s|%s",
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
                            printf("%s", ctime(&now));
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
                        if (ulhead->u.ut_type != DEAD_PROCESS)
                        {
                            printf("%s", ctime(&now));
                            printf("Added:\n%8.8s|%16.16s|%8.8s|%s",
                                   ulhead->u.ut_user, ulhead->u.ut_host,
                                   ulhead->u.ut_line, ctime(&ulheadt));
                        }

                        tmpul->next = ulhead;
                    }
                }
            }
            ulhead = reful;

            /*while (ulhead->next != NULL)
            {
                if (ulhead->u.ut_type != DEAD_PROCESS)
                {
                    time_t t = ulhead->u.ut_tv.tv_sec;
                    printf("%8.8s|%16.16s|%8.8s|%s", ulhead->u.ut_user,
                           ulhead->u.ut_host, ulhead->u.ut_line, ctime(&t));
                }
                ulhead = ulhead->next;
            }
            if (ulhead->u.ut_type != DEAD_PROCESS)
            {
                time_t t = ulhead->u.ut_tv.tv_sec;
                printf("%8.8s|%16.16s|%8.8s|%s", ulhead->u.ut_user,
                       ulhead->u.ut_host, ulhead->u.ut_line, ctime(&t));
            }
            printf("------reful end------\n");*/
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