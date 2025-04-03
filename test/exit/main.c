#include <ctype.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINEBUF_MAX 2048

int is_numeric(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (str[i] == '\0')
        return (0);
    while (str[i] != '\0') //数字かチェック
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

// 文字列をllong型に変換する関数
long long ft_atoll(const char *str)
{
    long long result;
    int sign;
    int i;

    result = 0;
    sign = 1;
    i = 0;

    // 空白をスキップ
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    
    // 符号の処理
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    
    // 数値変換
    while (str[i] >= '0' && str[i] <= '9')
    {
        // オーバーフローチェック
        if (result > LLONG_MAX / 10 || 
            (result == LLONG_MAX / 10 && str[i] - '0' > LLONG_MAX % 10))
            return (sign == 1 ? LLONG_MAX : LLONG_MIN);
        
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return (result * sign);
}

void ft_exit(char *line, char *envp[])
{
    int i;
    int j;
    char arg[LINEBUF_MAX];
    int arg_count;
    long long value;

    if (strncmp(line, "exit", 4) != 0)
    {
        printf("command not found: %s\n", line);
        return;
    }

    printf("exit\n"); // bash同様、exitを表示

    // exit の後の空白をスキップ
    i = 4;
    while (line[i] == ' ')
        i++;

    // 引数がない場合は通常終了（ステータス0）
    if (line[i] == '\0')
        exit(0);

    // 第1引数を取得
    j = 0;
    while (line[i] != '\0' && line[i] != ' ')
        arg[j++] = line[i++];
    arg[j] = '\0';

    // 数値かどうかチェック
    if (!is_numeric(arg))
    {
        printf("bash: exit: %s: numeric argument required\n", arg);
        exit(2);
    }

    // 数値を変換
    value = ft_atoll(arg);

    // 追加の引数があるかチェック
    while (line[i] == ' ')
        i++;
    
    if (line[i] != '\0')
    {
        printf("bash: exit: too many arguments\n");
        return; // 複数引数ある場合は終了しない
    }

    // 終了ステータスを計算（0-255の範囲に収める）
    exit((unsigned char)value);
}

int	main(void)
{
	char *line;
	extern char **environ;
	while (1)
	{
		line = readline("$");
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			ft_exit(line, environ);
		}
		free(line);
	}
	exit(0);
}