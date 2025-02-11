# 斐波那契堆 复杂度分析报告

本文使用小根堆进行说明。

## 斐波那契堆简介

### 结构

斐波那契堆的每个节点的子节点数不固定，
存储时使用孩子-兄弟表示法，
层内由双向链表连接。

最上面一层双向链表称为根链。

根指针指向根链上的最小节点。

### 操作

* push操作

  直接在根链中插入新节点，并更新根指针。

* merge操作

  将两个根链断开并连接，更新根指针。

* top操作

  直接取根指针所指向的值。

* pop操作

  将根节点删除，将其子节点的链表并入根链。

  对根链做整理，如果有具有相同度数的两棵树，就将其中值较大一颗加入另一颗的子节点链中。
（如果没有decrease_key操作，那么一棵树的点数取以二为底的对数就是其度数）

* decrease_key 操作

  * 减小后的值比父节点大，不做处理

  * 比父节点小，将该点直接移动到根链。并尝试对父节点打标记。如果父节点已存在标记，就将父节点移至根链，并递归尝试对父节点的父节点打标记。

  在本次作业中，不涉及此操作，所以以下复杂度分析中不考虑该操作。

### 单次复杂度分析

* push $O(1)$

* merge $O(1)$

* top $O(1)$

* pop 最差 $O(n)$

* decrease_key 最多递归树高次，显然为 $O(\log n)$。

## 一些准备

### 分析方法

采用势能法进行摊还分析。
对于数据结构 $D$，初始状态 $D_0$，经过第 $i$ 次操作后变成 $D_i$。

若有函数 $\Phi:\{D_k\}\to \mathbb{R}$，满足 $\forall n$,
$$
\Phi(D_n)\ge \Phi(D_0)
$$
则称 $\Phi$ 是数据结构 $D$ 的势函数。

即第 $i$ 次操作的代价为 $c_i$。
定义 $\hat c_i = c_i + \Phi(D_i)-\Phi(D_{i-1})$ 为第 $i$ 次操作的摊还代价。

则
$$
\sum_{i=1}^{n}\hat{c_i}=\sum_{i=1}^{n}c_i + \Phi(D_n)-\Phi(D_0)
$$
给出 $n$ 次操作的实际代价的上界。

### 定义

$H$ 表示斐波那契堆

$t(H)$ 为树的个数，即根链的大小。

$m(H)$ 为被标记的点的个数。

$s(p)$ 表示以 $p$ 的子节点数量。

### 引理

* 每个点的子节点个数是 $\log n$。

* 经过一次对根链的整理后，根链不大于 $\log n$。

## 分析

### 不考虑 decrease_key

定义势函数
$\Phi(H)=t(d)$。

$H_0$ 为空堆，则显然 $\Phi(H)\ge 0=\Phi(H_0)$。

* push. 修改最多三个节点的信息。$\Phi(H')=\Phi(H)+1$，所以 $\hat{c}=3+1=4=O(1)$。

* merge. 修改四个节点。
 $\Phi(H')=\Phi(H_1)+\Phi(H_2)$。
 $\hat{c}=4+0=4=O(1)$。

* top. $\hat{c}=c=1=O(1)$.

* pop. $c=t(H)+s(p)$.
 因为 $\Phi(H')=O(\log n)$，
 所以
 $$
 \hat{c}=t(H)+s(p)+\Phi(H')-t(H)=s(p)+\Phi(H')=O(\log n)
 $$

### 考虑 decrease_key

定义 $\Phi(H)=t(H)+2m(H)$。

push,merge,top操作的证明不变。

对于 decrease_key 操作，设一共将 $x$ 个节点移到根链，则 $c = x$.

$t(H')-t(H)=x$，$m(H')\le m(H)-x+1$.

$$
\hat{c}\le x+x+2(1-x)=O(1)
$$


对于pop操作，上文中用到的一条性质是存疑的。

> 经过一次对根链的整理后，根链不大于 $\log_2 n$。

这条性质依赖于每个节点的大小都是 $2^k$。
但是在有 decrease_key 操作下，一个节点的子节点可以被删除。
因此如果不做任何处理，每次 decrease_key 都只把改变的节点放到根链上，不能保证树的度和大小有指数关系。


斐波那契树通过打标记来解决这个问题。

> 在 decrease 一个节点时，如果移动，就会给父节点打标记。
 一个节点被第二次被打标记时，会直接移动到根，并对其原本的父节点打标记。

这样的操作保证了一个点最多有一个直接子节点被删除。

因此，我们可以设度数为 $n$ 的子树的最小节点数量为 $f(n)$，则 $f$ 满足递推式
$$
f(n)=f(n-1)+f(n-2)
$$

解释一下：考虑度数为 $n$ 的树如何由两颗度数为 $n-1$ 的树构成。
首先度数为 $n-1$ 的最小树中，首先其度数为 $n-2$ 的子树应当是被删去的。
考虑度数为 $n$ 的完整树变成最小树的过程，先把 $n-1$ 的子树删去，
然后把剩下的部分逐个调整为最小的。
因此度数为 $n$ 的最小树比度数为 $n-1$ 的最小树多了一个度数为 $n-2$ 的子树。

考虑合并方法仍然是“相同度数合并”，因为 $2f(n)>f(n+1)$，所以 $f$ 确实给出了斐波那契堆中树的最小值。该最小值的递推关系，也就是斐波那契堆名字的由来。

斐波那契数列渐进于公比为 $\frac{\sqrt5 + 1}{2} \approx 1.6180$ 的等比数列。
在整理后的根链中，最坏情况下，从0开始度数连续出现，而且每一棵树都是最小树。
此时，根链的大小是 $O(\log_{\frac{\sqrt5 + 1}{2}}n)$ 的，
所以 pop 的均摊复杂度的量级仍为 对数。

## 参考文献

[1] 优雅永不过时,斐波那契堆与摊还分析,知乎,[https://zhuanlan.zhihu.com/p/595328059](https://zhuanlan.zhihu.com/p/595328059).

[2] 百度百科,斐波那契数列,[https://baike.baidu.com/item/百度百科](https://baike.baidu.com/item/百度百科).

[3] 维基百科,斐波那契堆,[https://zh.wikipedia.org/wiki/斐波那契堆](https://zh.wikipedia.org/wiki/斐波那契堆).
