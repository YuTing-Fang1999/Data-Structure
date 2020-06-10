# 1, 2
### [四維陣列轉一維陣列](https://openhome.cc/Gossip/AlgorithmGossip/MultiToOneDim.htm)
```
以列為主：loc = i*u2*u3 + j*u3 + k
以行為主：loc = k*u1*u2 + j*u1 + i
```
# 3
### 背包問題，求背包可放入的最大重量，使用動態規劃
```cpp
//w: 背包重量 
//weight[i]: 第i個物品重量 
//item[w]: 最後一個裝滿重量 w 的物品重量 

	//如果不能裝入 
	if(weight[i] > W) break;
	//直接填滿目前的空背包 w 
	if ((item[w] == 0) && (weight[i] == w)) {
		item[w] = i;
	}
	//  如果   可累裝      且 此空間為w + weight[i]的背包還沒被裝滿過
	else if((item[w] > 0) && (item[w + weight[i]]==0) 
				//且 (不超過目標大小W)    且  不能自己累加
				&& ((w + weight[i])<=W) && (item[w] != i)){
		item[w + weight[i]] = i;
	}
	
//最後從item[W](W: 目標背包重量)遞減-1，找出從哪裡開始不為0就是最大背包重
 ```
# 4
### 物品可拆碎放入，求放入的最大價格
```
用單位價格排序，由大排到小，依序放入直到背包滿
```
# 5
### 最短路徑
使用dijkstra  
找離原點最近的點v依序更新其他點w  
如果經由v到w的距離會小於目前到w的距離就更新disTo\[w\]  
```java
public class DijkstraSP
{
   private DirectedEdge[] edgeTo;
   private double[] distTo;
   private IndexMinPQ<Double> pq;

   public DijkstraSP(EdgeWeightedDigraph G, int s)
   {
   	//初始化
      edgeTo = new DirectedEdge[G.V()];
      distTo = new double[G.V()];
      pq = new IndexMinPQ<Double>(G.V());

      for (int v = 0; v < G.V(); v++) //初始距離無限大
         distTo[v] = Double.POSITIVE_INFINITY;
      distTo[s] = 0.0;

      pq.insert(s, 0.0);
      while (!pq.isEmpty())
      {
          int v = pq.delMin();
          for (DirectedEdge e : G.adj(v)) //更新與v相連的節點的距離
             relax(e);
      }
    }
 }
 private void relax(DirectedEdge e)
   {
      int v = e.from(), w = e.to();
      if (distTo[w] > distTo[v] + e.weight()) 如果經由v到w的距離會小於目前到w的距離就更新disTo[w]
      {
          distTo[w] = distTo[v] + e.weight();
          edgeTo[w] = e; //用來求路徑的，此題只求距離所以可省略
          if (pq.contains(w)) pq.decreaseKey(w, distTo[w]); //如果pq裡已有w就更新
          else                pq.insert     (w, distTo[w]); //放入pq
      }       
   }

```
