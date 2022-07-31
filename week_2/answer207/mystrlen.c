#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 最も基本的な方法。
// 一つ一つ文字計算の方法。
size_t my_strlen1(const char* s)
{
	const char* t = s;

	while (*t++);

	return t - s - 1;
}

// 少し試してみたかっただけで、
// my_strlen1の結果と同じ効果になるはずだと思っていましたが、
// 予想外に良い結果が得られましたが、
// まだ strlen ほどではありませんでした。
size_t my_strlen2(const char* s)
{
	size_t n = 0;

	if (*s == 0)
	{
		return n;
	}

	while (1)
	{
		if (*(s + 1) == 0)
		{
			return n + 1;
		}
		if (*(s + 2) == 0)
		{
			return n + 2;
		}
		if (*(s + 3) == 0)
		{
			return n + 3;
		}
		if (*(s + 4) == 0)
		{
			return n + 4;
		}
		if (*(s + 5) == 0)
		{
			return n + 5;
		}
		if (*(s + 6) == 0)
		{
			return n + 6;
		}
		if (*(s + 7) == 0)
		{
			return n + 7;
		}
		if (*(s + 8) == 0)
		{
			return n + 8;
		}
		n += 8;
		s += 8;
	}
}

// my_strlen1 の改善された方法は、
// 2 文字ごとにチェックすることで、
// my_strlen1 の結果を半分の時間で取得したいと考えており、
// 実行結果は my_strlen1 の約 50 ～ 80 % 程度です。
// 欠点1：実行できるもののbufferのsizeを超える可能性があります。
// 欠点2：string途中に'\0'があるとチェックされない場合がある。
size_t my_strlen3_1(const char* s)
{
	size_t n = 0;

	while (*s > 0 && *s <= 127)
	{
		n += 2;
		s += 2;
	}

	while (*--s <= 0 || *--s > 127)
	{
		--n;
	}

	return n;
}

// my_strlen3_1の改良された方法で、
// チェックする文字数を減らすことでプログラムを高速化しようとしていますが、
// strlen の速度に達するか、それを超えることさえありますが、多くの欠点があります。
// 欠点1：実行はできるが、buffer sizeをoverしやすい。
// 欠点2：string途中に'\0'があるとチェックされない場合がある。
// 欠点 3: buffer sizeが大きくないと、間違った結果が得られやすくなります。
size_t my_strlen3_2(const char* s)
{
	size_t n = 0;

	while (*s > 0 && *s <= 127)
	{
		n += 40;
		s += 40;
	}

	while (*--s == 0)
	{
		--n;
	}

	return n;
}

//もともとbinary searchで'\0'を検索したかったのですが、
//buffer sizeが分からずsegmentation faultを起こすことがわかったので中止しました。
/*size_t my_strlen4(const char* s)
{
	size_t n = 10;
	size_t x = 0;

	while (*(s + n) <= 127 && *(s + n) >= 0)
	{
		x = n;
		n = n * 1.5;
	}

	while (n - x > 2)
	{
		if (*(s + (n - x) / 2) >= 0 && *(s + (n - x) / 2) <= 127)
		{
			x = (n - x) / 2;
		}

		else
		{
			n = (n - x) / 2;
		}
	}

}*/

//buffer sizeがわかったら、
//binary searchを使います。
//欠点1：string途中に'\0'があるとチェックされない場合がある。
size_t my_strlen4(const char* s, size_t n)
{
	size_t low = 0;
	size_t high = n;
	size_t mid;

	while (high >= low)
	{
		mid = (high + low) / 2;

		if (*(s + mid) == 0)
		{
			return mid;
		}

		else if (*(s + mid) > 127 || *(s + mid) < 0)
		{
			high = mid - 1;
		}

		else if (*(s + mid) <= 127 && *(s + mid) >= 0)
		{
			low = mid + 1;
		}
	}
}

char* string_make(size_t n)
{
	char* str = (char*)malloc(sizeof(char) * n);
	char* s = str;
	srand((unsigned)time(NULL));

	for (int i = 0; i < n - 1; i++)
	{
		*str = rand() % (127 - 32) + 32;
		str++;
	}

	*str = 0;

 	return s;
}

int main()
{
	char* s;
	double start, end;
	size_t n, n1, n2, n3_1, n3_2, n4;
	int buff_size = 2048000000;

	printf("buffer size:%d bytes\n\n", buff_size);

	s = string_make(buff_size);

	start = clock();
	n = strlen(s);
	end = clock();
	printf("strlen result:%zu   use time:%lf(s)\n\n", n, (end - start) / CLOCKS_PER_SEC);

	start = clock();
	n1 = my_strlen1(s);
	end = clock();
	printf("my_strlen1 result:%zu   use time:%lf(s)\n\n", n1, (end - start) / CLOCKS_PER_SEC);

	start = clock();
	n2 = my_strlen2(s);
	end = clock();
	printf("my_strlen2 result:%zu   use time:%lf(s)\n\n", n2, (end - start) / CLOCKS_PER_SEC);

	start = clock();
	n3_1 = my_strlen3_1(s);
	end = clock();
	printf("my_strlen3_1 result:%zu   use time:%lf(s)\n\n", n3_1, (end - start) / CLOCKS_PER_SEC);

	start = clock();
	n3_2 = my_strlen3_2(s);
	end = clock();
	printf("my_strlen3_2 result:%zu   use time:%lf(s)\n\n", n3_2, (end - start) / CLOCKS_PER_SEC);

	start = clock();
	n4 = my_strlen4(s, buff_size);
	end = clock();
	printf("my_strlen4 result:%zu   use time:%lf(s)\n\n", n4, (end - start) / CLOCKS_PER_SEC);

	free(s);

	return 0;
}
