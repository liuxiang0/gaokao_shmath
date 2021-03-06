/*
Stein算法(以下理论请参考http://blog.vckbase.com/arong/archive/2004/06/15/458.html），
代码是我加上的。

欧几里德算法是计算两个数最大公约数的传统算法，他无论从理论还是从效率上都是很好的。
但是他有一个致命的缺陷，这个缺陷只有在大素数时才会显现出来。
考虑现在的硬件平台，一般整数最多也就是64位，对于这样的整数，计算两个数之间的模是很简单的。
对于字长为32位的平台，计算两个不超过32位的整数的模，只需要一个指令周期，而计算64位以下的整数模，
也不过几个周期而已。但是对于更大的素数，这样的计算过程就不得不由用户来设计，为了计算两个超过64位
的整数的模，用户也许不得不采用类似于多位数除法手算过程中的试商法，这个过程不但复杂，而且消耗了很
多CPU时间。对于现代密码算法，要求计算128位以上的素数的情况比比皆是，设计这样的程序迫切希望能够
抛弃除法和取模。

Stein算法由J. Stein 1961年提出，这个方法也是计算两个数的最大公约数。和欧几里德算法 算法不同的是，
Stein算法只有整数的移位和加减法，这对于程序设计者是一个福音。

为了说明Stein算法的正确性，首先必须注意到以下结论：

gcd(a,a) = a，也就是一个数和他自身的公约数是其自身 
gcd(ka,kb) = k gcd(a,b)，也就是最大公约数运算和倍乘运算可以交换，
特殊的，当k=2时，说明两个偶数的最大公约数必然能被2整除 
有了上述规律就可以给出Stein算法如下：

1.如果A=0，B是最大公约数，算法结束 
2.如果B=0，A是最大公约数，算法结束 
3.设置A1 = A、B1=B和C1 = 1 
4.如果An和Bn都是偶数，则An+1 =An /2，Bn+1 =Bn /2，Cn+1 =Cn *2(注意，乘2只要把整数左移一位即可，除2只要把整数右移一位即可) 
5.如果An是偶数，Bn不是偶数，则An+1 =An /2，Bn+1 =Bn ，Cn+1 =Cn (很显然啦，2不是奇数的约数) 
6.如果Bn是偶数，An不是偶数，则Bn+1 =Bn /2，An+1 =An ，Cn+1 =Cn (很显然啦，2不是奇数的约数) 
7.如果An和Bn都不是偶数，则An+1 =|An -Bn|，Bn+1 =min(An,Bn)，Cn+1 =Cn 
8.n++，转4 
这个算法的原理很显然，所以就不再证明了。现在考察一下该算法和欧几里德方法效率上的差别。

考虑欧几里德算法，最恶劣的情况是，每次迭代a = 2b -1,这样，迭代后，r= b-1。
如果a小于2N，这样大约需要 4N次迭代。而考虑Stein算法，每次迭代后，显然AN+1BN+1≤ ANBN/2，
最大迭代次数也不超过4N次。也就是说，迭代次数几乎是相等的。
但是，需要注意的是，对于大素数，试商法将使每次迭代都更复杂，因此对于大素数Stein将更有优势。

其算法用C++语言描述为：
*/
bool is_even(int n) 
{
 return !(n & 1);
}
int gcd2(int m, int n)
{
 int c = 1;
 while (m != 0 && n != 0)
 {
  if (is_even(m) && is_even(n))
  {
   m >>= 1;
   n >>= 1;
   c <<= 1;
  }
  else if (is_even(m) && !is_even(n))
  {
   m >>= 1;
  }
  else if (!is_even(m) && is_even(n))
  {
   n >>= 1;
  }
  else if (!is_even(m) && !is_even(n))
  {
   int m1 = m;
   int n1 = n;
   m = abs(m-n);  //crt库函数
   n = min(m1, n1);//crt宏
  }
 }

 return c * n;
}
