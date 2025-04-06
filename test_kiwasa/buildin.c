#include "minishell.h"

int buildin_echo(void)
{
    return (0);
}

int buildin_exit(void)
{
    printf("buildin_exit called\n");
    exit(0);
    return (0);
}

int buildin_cd(void)
{
    printf("buildin_cd called\n");
    return (0);
}

int buildin_pwd(void)
{
    char	cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd error");
    return (0);
}

int buildin_export(void)
{
    // 環境変数の設定などを実装する
    printf("buildin_export called\n");
    return (0);
}

int buildin_unset(void)
{
    // 環境変数の削除などを実装する
    printf("buildin_unset called\n");
    return (0);
}

int buildin_env(void)
{
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);
    return (0);
}