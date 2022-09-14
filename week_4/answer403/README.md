``` c
int main(void)
{
    fork();
    fork();
    fork();
    printf("Hello.\n");
    wait(NULL);
    return 0;
}
```

最初のforkで子プロセスが作成され、次の2つのforkで4になります。  
したがって、4つの Hello.があります。  

2番目のforkは別の子プロセスを作成し、最後のforkは2つになります。  
したがって、2つのHello.があります。  

3番目のフォークは子プロセスを作成し、1つのHello.を生成します。  

最後に、Hello.を生成するprintf自体があり、合計8つのHello.。