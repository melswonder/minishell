#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// int main(void)
// {
//     char *rl;
//     rl = readline("Prompt > ");
//     rl_redisplay();
//     printf("%s\n", rl);
//     rl_redisplay();
//     return (0);
// }

//cc test.c -lreadline -lncurses

//---⇡readline⇡---

// #include <unistd.h>
// #include <stdio.h> // for printf
// #define PATH_MAX 10

// int main(void)
// {
//     char *pwd;
//     char path[PATH_MAX];

//     pwd = getcwd(NULL, 0); //必要なサイズ自動確保　動的の場合はfreeする。
//     getcwd(path, sizeof(PATH_MAX)); //自分でサイズを決められる
//     printf("pwd: %s\n", pwd);
//     return (0);
// }

//--pwd--

// #include <unistd.h>
// #include <stdio.h> // for printf

// int main(void)
// {
//     char *pwd;
    
//     pwd = getcwd(NULL, 0);
//     printf("pwd before chdir: %s\n", pwd);
//     chdir("/home/hirwatan/42/workspase/minishell/");
//     pwd = getcwd(NULL, 0);
//     printf("pwd after chdir: %s\n", pwd);
//     return (0);
// }

//---cd=---

// #include<stdlib.h>
// #include<stdio.h>
// int main(void)
// {
//   char *path;
//   path = getenv("USER_ZDOTDIR");
//   printf("%s",path);
// }
//--env

///
// de-git-70f934720a.sock
// VSCODE_INJECTION=1
// ZDOTDIR=/home/hirwatan
// USER_ZDOTDIR=/home/hirwatan
///
/// /home/hirwatan