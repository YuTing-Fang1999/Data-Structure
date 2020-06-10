# 1, 2
### [四維陣列轉一維陣列](https://openhome.cc/Gossip/AlgorithmGossip/MultiToOneDim.htm)
```
以列為主：loc = i*u2*u3 + j*u3 + k
以行為主：loc = k*u1*u2 + j*u1 + i
```
# 3
### 背包問題，求背包可放入的最大重量，使用動態規劃
```
//w: 背包重量 
//weight[i]: 第i個物品重量 
//item[w]: 最後一個裝滿重量 w 的物品重量 

	//如果不能裝入 
	if(weight[i] > W) break;
	//直接填滿目前的空背包 w 
	if ((item[w] == 0) && (weight[i] == w)) {
		item[w] = i;
	}
	//如果此重w的背包可累裝且還有空間裝入且只裝一次 
	else if((item[w] > 0) && (item[w + weight[i]]==0) 
				&& ((w + weight[i])<=W) && (item[w] != i)){
		item[w + weight[i]] = i;
	}
//最後從item[w](w: 背包重量)遞減-1，找出從哪裡開始不為0就行
 ```cpp
# 4
### 物品可拆碎放入，求放入的最大價格，直接由大排到小放入
# 5
### 最短路徑
