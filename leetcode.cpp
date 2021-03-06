//============================================================================
// Name        : leetcode.cpp
// Author      : kiddinglife
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <exception>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

using namespace std;

// 1. Two Sum https://leetcode.com/problems/two-sum/description/
static vector<int> twoSum(vector<int>& nums, int target)
{
  /*
   int size = nums.size();
   vector<int> ret;
   for (int i = 0; i < size; ++i)
   {
   int find = target - nums[i];
   for (int j = i + 1; j < size; ++j)
   {
   if (find == nums[j])
   {
   ret.push_back(i);
   ret.push_back(j);
   return ret;
   }
   }
   }
   return ret;

   //complexity: o(n power 2)
   //bottle neck: loops
   //improvement:
   //hash table
   //hashtable search b in the left of a : tartget - a = hashed(b)
   //for right wait loop go forwards: tartget - b = hash(a)

   // use unordered_map o(n)
   int size = nums.size();
   vector<int> ret;
   unordered_map<int, int> hash;
   for (int i = 0; i < size; ++i)
   {
   int val = target - nums[i];
   auto itr = hash.find(val);
   if (itr != hash.end())
   {
   ret.push_back(itr->second);
   ret.push_back(i);
   return ret;
   }
   hash.insert(pair<int, int>(nums[i], i));
   }
   return ret;
   */
  vector<int> ret(2);
  int size = nums.size();
  if (size < 2)
    return ret;
  unordered_multimap<int, int> idxs;
  for (int i = 0; i < (int) nums.size(); ++i)
    idxs.insert(pair<int, int>(nums[i], i));
  sort(nums.begin(), nums.end());
  int left = 0;
  int right = size - 1;
  while (left < right)
  {
    if ((nums[left] + nums[right]) > target)
      --right;
    else if ((nums[left] + nums[right]) < target)
      ++left;
    else
    {
      if (idxs.find(nums[left])->first == idxs.find(nums[right])->first)
      {
        auto rett = idxs.equal_range(nums[left]);
        //for (auto it = rett.first; it != rett.second; ++it)
        //	std::cout << it->second;
        //cout << endl;
        ret[0] = rett.first->second + 1;
        ++rett.first;
        ret[1] = rett.first->second + 1;
      }
      else
      {
        ret[0] = idxs.find(nums[left])->second + 1;
        ret[1] = idxs.find(nums[right])->second + 1;
      }
      break;
    }
  }
  return ret;
}

// 1. Two Sum sorted  https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
static vector<int> twoSumSorted(vector<int>& nums, int target)
{
  vector<int> ret(2);
  int size = nums.size();
  if (size < 2)
    return ret;

  int left = 0;
  int right = size - 1;

  while (left < right)
  {
    if ((nums[left] + nums[right]) > target)
      --right;
    else if ((nums[left] + nums[right]) < target)
      ++left;
    else
    {
      ret[0] = left + 1;
      ret[1] = right + 1;
      break;
    }
  }
  return ret;
}

static vector<vector<int> > threeSum(vector<int>& nums)
{
  // my first solution leetcode 800ms all passed using multimap
  // not very fast
  //* input [-1,2,0,1,0,-1,....]
  //* ouput [-1,1,0]
  //* -1,2 seek  -1 in [0, 1]
  //* -1,0 seek   1 in [2, 1]
  //* -1,1 seek   0 in [2, 0]
  //*  2,0 seek  -2 in [-1,1]

  //vector<vector<int> > ret;
  //int size = nums.size();
  //if (size < 3)
  //	return ret;

  //set<int> ss;
  //ss.insert(nums.begin(), nums.end());
  //if (ss.size() == 1)
  //{
  //	if (nums[0] == 0)
  //		ret.push_back(vector<int>(3, 0));
  //	return ret;
  //}

  //set<vector<int>> s;
  //vector<int> triple(size_t(3));
  //unordered_multimap<int, pair<int, int> > hash;
  //sort(nums.begin(), nums.end());
  //bool same_triple = false;

  //for (int i = 0; i < size; ++i)
  //{
  //	int j = i + 1;
  //	while (j < size)
  //	{
  //		if (nums[j] > 0)
  //			break;

  //		if (nums[j - 1] == nums[j] && nums[j] == nums[i])
  //			same_triple = true;
  //		else
  //			same_triple = false;
  //		if (j - i > 1 && ((same_triple && nums[j - 1] != 0) || !same_triple))
  //		{

  //			int find = nums[j];
  //			auto itr = hash.find(find);
  //			if (itr != hash.end())
  //			{
  //				cout << "--> found: " << find << ", " << i << ", " << j << endl;
  //				triple[0] = itr->second.first;
  //				triple[1] = itr->second.second;
  //				triple[2] = find;
  //				//ret.push_back(triple);
  //				s.insert(triple);
  //				same_triple = false;
  //			}
  //		}
  //		// ignore all duplicated values but keys can be duplicated
  //		if (j - i == 1 || nums[j - 1] != nums[j])
  //		{
  //			int add = -(nums[i] + nums[j]);
  //			cout << "add: " << add << ", " << nums[i] << ", " << nums[j] << ", " << endl;
  //			if (hash.find(add) == hash.end())
  //				hash.insert(pair<int, pair<int, int>>(add, pair<int, int>(nums[i], nums[j])));
  //		}
  //		j++;
  //	}
  //	// must clear hash
  //	//    for (auto itr = hash.begin(); itr != hash.end(); ++itr)
  //	//      cout << "add: " << itr->first << ", " << itr->second.first << ", " << itr->second.second << endl;
  //	//    cout << endl;
  //	hash.clear();
  //}

  //ret.assign(s.begin(), s.end());
  //return ret;

  // second solution using sort and two pointers
  vector<vector<int> > ret;
  int size = nums.size();
  int originsize = size;
  if (size < 3)
    return ret;

  sort(nums.begin(), nums.end());
  //for (size_t i = 0; i < nums.size(); i++)
  //	std::cout << nums[i] << ":" << i <<", ";
  //std::cout << endl;

  int max_num = nums.back();
  if (max_num < 0)
    return ret;
  int min_num = nums.front();
  if (min_num > 0)
    return ret;

  int left, right; // defines search range
  size -= 2; // -2 is to stop when less than 3 numbers
  vector<int> triple(size_t(3));
  int sum;

  for (int i = 0; i < size; ++i)
  {
    // 	all numbers after number 1 are greater than 0
    // example: 1(i)  [2(left)] 222222  33333[3(right)]
    if (nums[i] > 0)
      break;

    // bypass duplicate numbers at index of i
    // example:  00 111111111111[1(i)] 222222  33333
    while (i < size - 1 && nums[i] != 0 && nums[i] == nums[i + 1] && nums[i + 1] == nums[i + 2])
    {
      ++i;
    }

    left = i + 1;
    right = originsize - 1;

    // all numbers after number 1 are greater than 0
    // example: 0(i) [1(left)]1111 222222  33333[3(right)]
    if (nums[i] == 0 && nums[left] > 0)
      break;

    // why not use left != right
    // example:  0(i=0) [-1(left=1)]  [1(right=2)]
    // after left ++ and right --
    // [2 = left] != [right = 1 ]
    // this will cause while loop never ends
    while (left < right)
    {
      // @remember me: should not bypass here
      // example:
      // -5, -5, -4, -4, -4, -2, -2, -2(i), 0(left), 0, 0, 1, 1, 3(right), 4, 4 -> after bypass =>
      // -5, -5, -4, -4, -4, -2, -2, -2(i=7), 0, 0, 0(left), 1(right=11), 1, 3, 4, 4,
      // -5, -5, -4, -4, -4, -2, -2, -2(i=7), 0, 0, 0, 1(left,right=11), 1, 3, 4, 4,
      // as you see -2, 1 , 1 is missed which is kind of bug.
      // the solution is to move this section of codes to section where sum == 0
      // only in this case we can safely bypass the duplicates
      //while (right - left > 2 && nums[left-1] == nums[left + 1]) { ++left; }
      //while (right - left > 2 && nums[right] == nums[right - 1]) { --right; }

      // example:
      // -5(i) [-3(left)] -2           -1 0 1 2 3 5 6  7              8             [9(right)] -> sum = -5-3+9=1 > 0, --right =>
      // -5(i) [-3(left)] -2           -1 0 1 2 3 5 6  7             [8(right)]  9  -> found -5-3+8=0, --right, ++left =>
      // -5(i)  -3         [-2(left)]  -1 0 1 2 3 5 6 [7(right)]  8              9
      // ...... comtinue the above procedure and finally =>
      // -5(i)  -3  -2  -1 0 1 [2(right)] [3(left)] 5 6 7  8 9 -> left > right => while loop stops
      sum = nums[i] + nums[left] + nums[right];
      if (sum > 0)
        --right;
      else if (sum < 0)
        ++left;
      else
      {
        triple.assign( { nums[i], nums[left], nums[right] });
        //for (size_t i = 0; i < 3; i++)
        //	std::cout << triple[i] << " ";
        //std::cout << endl;
        ret.push_back(triple);

        // bypass duplicate numbers in search range defined by left and right only whenthe triple is found
        // example:  0(i) -1-1-1-1-1[-1(left)] 11111 222222 [3(right)] 33333
        // after bypass, lfet is at the rightmost number -1, right is at the leftmost number 3
        while (left < right && nums[left] == nums[left + 1])
        {
          ++left;
        }
        while (right > left && nums[right] == nums[right - 1])
        {
          --right;
        }

        // bypass duplicated numbers at index i only whenthe triple is found
        // example:  -1 -1(i) 0(left) 1(right), need to bypass the other -1 0 1
        while (i < left && nums[i] == nums[i + 1])
        {
          i++;
        }

        ++left;
        --right;
      }
    }
  }
  return ret;
}

// https://leetcode.com/problems/3sum-closest/description/
static int threeSumClosest(vector<int>& nums, int target)
{
  int size = nums.size();
  int originsize = size;
  int ret;
  if (size <= 3)
  {
    ret = 0;
    for (size_t i = 0; i < nums.size(); i++)
      ret += nums[i];
    return ret;
  }

  int mindiff = 0;
  sort(nums.begin(), nums.end());

  size_t left, right; // defines search range
  size -= 2; // -2 is to stop when less than 3 numbers
  int sum;

  for (int i = 0; i < size; ++i)
  {
    left = i + 1;
    right = originsize - 1;
    while (left < right)
    {
      sum = nums[i] + nums[left] + nums[right];
      if (sum > target)
        --right;
      else if (sum < target)
        ++left;
      else
        return target;

      int dis = abs(sum - target);
      if (mindiff == 0 || mindiff > dis)
      {
        mindiff = dis;
        ret = sum;
      }
    }
  }
  return ret;
}

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
static int removeDuplicates(vector<int>& nums)
{
  size_t size = nums.size();
  if (size == 0)
    return 0;
  size_t pos = 0;
  for (size_t i = 0; i < size - 1; i++)
  {
    if (nums[i] != nums[i + 1])
    {
      pos++;
      nums[pos] = nums[i + 1];
    }
  }
  return pos + 1;
}

// https://leetcode.com/problems/remove-element/description/
static int removeElement(vector<int>& nums, int val)
{
  // 0 1 2 3 4 5  6 7 8 9
  // 0 1 1 1 3 0  4 2 1 1
  // 0 3 0 4 2 0' 4 2
  size_t vsize = nums.size();
  int pos = -1;
  for (size_t i = 0; i < vsize; i++)
  {
    if (pos == -1)
    {
      if (nums[i] == val)
        pos = i;
    }
    else if (nums[i] != val)
    {
      nums[pos] = nums[i];
      pos++;
    }
  }
  return pos == -1 ? vsize : pos;
}

/*
 Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array),
 some elements appear twice and others appear once.
 Find all the elements of [1, n] inclusive that do not appear in this array.
 Could you do it without extra space and in O(n) runtime? You may assume the
 returned list does not count as extra space.

 Example:
 Input:
 [4,3,2,7,8,2,3,1]
 [-1,1,3]
 Output:
 [5,6]
 */
static vector<int> findDisappearedNumbers(vector<int>& nums)
{
  //  sort v1 slow 14.42% beats
  //  vector<int> ret;
  //  nums.push_back(0);
  //  int vsize = nums.size();
  //  nums.push_back(vsize);
  //  vsize++;
  //  int size = vsize -2;
  //  std::sort(nums.begin(), nums.end());
  //  for (int i = 0; i < vsize; ++i)
  //  {
  //    if(nums[i] > vsize)
  //      break;
  //
  //    if (i + 1 < vsize && nums[i+1] - nums[i] > 1)
  //    {
  //      int v = nums[i] + 1;
  //      do
  //      {
  //        if (v >= 1 && v <= size)
  //        {
  //          ret.push_back(v);
  //          v++;
  //        }
  //        else
  //          break;
  //      } while (v < nums[i+1]);
  //    }
  //  }
  //  return ret;

  // v2 notice that there is assuptio that nums is betwwen trnage of vector so use vector to mark existing munbers
  // this is faster than v1 as we save sort(), if n osuch assumption, sort(0 is more stable and faster
  // beats 97.87% 126ms
  int len = nums.size();
  vector<int> res;
  res.reserve(len / 2);
  int i, m;
  for (i = 0; i < len; i++)
  {
    m = abs(nums[i]) - 1; // index start from 0
    if (nums[m] > 0)
      nums[m] = -nums[m]; // must use -nums[m] as we may use it laters
  }
  for (i = 0; i < len; i++)
  {
    if (nums[i] > 0)
      res.push_back(i + 1);
  }
  return res;

}

/**
 Given an integer array nums, find the contiguous subarray
 (containing at least one number) which has the largest sum
 and return its sum.

 Example:
 Input: [-2,1,-3,4,-1,2,1,-5,4],
 Output: 6
 Explanation: [4,-1,2,1] has the largest sum = 6.

 Input: [1,-2,1, 2],
 Output: 6
 Explanation: [4,-1,2] has the largest sum = 5.]
 sum = -2, res = -2, min = -2;
 sum = -1, res = 1,

 Follow up:
 If you have figured out the O(n) solution, try coding
 another solution using the divide and conquer approach, which is more subtle.
 */
int maxSubArray(int A[], int n)
{
  int sum = 0, min = 0, res = A[0];
  for (int i = 0; i < n; i++)
  {
    sum += A[i];
    if (sum - min > res)
      res = sum - min;

    if (sum < min)
      min = sum;
  }
  return res;
}

/**
 https://leetcode.com/problems/rotate-array/description/
 Given an array, rotate the array to the right by k steps, where k is non-negative.

 Example 1:
 Input: [1,2,3,4,5,6,7] and k = 3
 Output: [5,6,7,1,2,3,4]
 Explanation:
 rotate 1 steps to the right: [7,1,2,3,4,5,6]
 rotate 2 steps to the right: [6,7,1,2,3,4,5]
 rotate 3 steps to the right: [5,6,7,1,2,3,4]

 Example 2:
 Input: [-1,-100,3,99] and k = 2
 Output: [3,99,-1,-100]
 Explanation:
 rotate 1 steps to the right: [99,-1,-100,3]
 rotate 2 steps to the right: [3,99,-1,-100]
 */
void array_rotate(vector<int>& nums, int k)
{
  int i, n = nums.size(), offset = 0;
  for (; k %= n; n -= k)
  {
    // Swap the last k elements with the first k elements.
    // The last k elements will be in the correct positions
    // but we need to rotate the remaining (n - k) elements
    // to the right by k steps.
    for (i = 0; i < k; i++)
      swap(nums[i + offset], nums[n - k + i + offset]);
    offset += i;
  }
}

/*
 4ms 95.45% beats
 Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 determine if the input string is valid.
 An input string is valid if:
 Open brackets must be closed by the same type of brackets.
 Open brackets must be closed in the correct order.
 Note that an empty string is also considered valid.
 */
bool isValid(string s)
{
  stack<char> vals;
  for (auto c : s)
  {
    if (c == '(' || c == '{' || c == '[')
      vals.push(c);
    else
    {
      if (vals.size() == 0)
        return false;
      char cc = vals.top();
      if ((cc == '(' && c == ')') || (cc == '{' && c == '}') || (cc == '[' && c == ']'))
        vals.pop();
      else
        return false;
    }
  }
  return vals.size() == 0;
}

/*
 假设数组为a[N]，max[N] 表示以下标为 i 结尾的子数组乘积最大值，
 min[N] 表示以下标为 i 结尾的子数组乘积最小值。
 为了处理数组元素为负的问题，必须将最小乘积也保存起来。
 很容易想到，若当前元素a[i]为负数，那么a[i]*max[i-1]得到的值并不一定比a[i]*min[i-1]大，
 因为min[i-1]可能为负，如果min[i-1]的绝对值大于max[i-1]，
 那么a[i]*min[i-1]负负相乘的值是更大的，因此有DP方程:
 curmax = MaxinThree(a[i],  a[i]*premax,  a[i]*premin);    //求三者最大
 curmin = MininThree(a[i],  a[i]*premax,  a[i]*premin);     //求三者最小
 */
int maxProduct(vector<int>& nums)
{
  int vsize = nums.size();
  if (vsize == 0)
    return 0;
  int premax = nums[0];
  int premin = nums[0];
  int res = premax;
  int curmax, curmin;
  printf("curmax: %d, curmin: %d, res: %d\n", premax, premin, res);
  for (int i = 1; i < vsize; i++)
  {
    curmax = max(max(premax * nums[i], premin * nums[i]), nums[i]);
    curmin = min(min(premax * nums[i], premin * nums[i]), nums[i]);
    res = max(curmax, res);
    printf("curmax: %d, curmin: %d, res: %d\n", curmax, curmin, res);
    premax = curmax;
    premin = curmin;
  }
  return res;
}

/*
 Example 1:
 Input: [7,1,5,3,6,4]
 Output: 5
 Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 Not 7-1 = 6, as selling price needs to be larger than buying price.

 Example 2:
 Input: [7,6,4,3,1]
 Output: 0
 Explanation: In this case, no transaction is done, i.e. max profit = 0.
 */
int maxProfit_i(vector<int>& prices)
{
  int vsize = static_cast<int>(prices.size());
  int maxprofit = 0;
  int sumprofit = 0;
  int curprofit;
  int buyprice = INT32_MAX;
  for (int i = 0; i < vsize; i++)
  {
    if (buyprice > prices[i])
      buyprice = prices[i];
    else
    {
      curprofit = prices[i] - buyprice;
      sumprofit += curprofit;
      if (curprofit > maxprofit)
        maxprofit = curprofit;
    }
  }
  return maxprofit;
}

/*
 Example 1:
 Input: [7,1,5,3,6,4]  0.
 Output: 7
 Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
 Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.

 Example 2:
 Input: [1,2,3,4,5]
 Output: 4
 Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
 Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
 engaging multiple transactions at the same time. You must sell before buying again.

 Example 3:
 Input: [7,6,4,3,1]
 Output: 0
 Explanation: In this case, no transaction is done, i.e. max profit = 0.

 DP idea is :
 the global max profit sum must be the sum up of all local max profit.
 */
int maxProfit_ii(vector<int>& prices)
{
  // basic idea is :
  // the global max profit sum must be the sum up of all local max profit.
  int vsize = static_cast<int>(prices.size());
  int maxprofit = 0;
  int maxprofitsum = 0;
  int curprofit;
  int buyprice = INT32_MAX;
  for (int i = 0; i < vsize; i++)
  {
    if (buyprice > prices[i])
    {
      // meet smaller buy price
      maxprofit = 0;
      buyprice = prices[i];
    }
    else
    {
      curprofit = prices[i] - buyprice;
      if (curprofit > maxprofit)
      {
        maxprofitsum -= maxprofit; // take away the smaller maxprofit
        maxprofit = curprofit;
        maxprofitsum += maxprofit; //then add the larger maxprofit
      }
      else
      {
        // meet a larger sell price
        buyprice = prices[i];
      }
    }
  }
  return maxprofitsum;
}
// http://zxi.mytechroad.com/blog/dynamic-programming/leetcode-300-longest-increasing-subsequence/
int findNumberOfLIS(vector<int>& nums)
{
  int n = nums.size(), maxlen = 1, numaxlen = 0;
  vector<int> cnt(n, 1), len(n, 1);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      if (nums[i] > nums[j])
      {
        if (len[j] + 1 > len[i])
        {
          len[i] = len[j] + 1;
          cnt[i] = cnt[j];
        }
        else if (len[j] + 1 == len[i])
          cnt[i] += cnt[j];
      }
    }
    if (maxlen < len[i])
    {
      maxlen = len[i];
      numaxlen = cnt[i];
    }
    else if (maxlen == len[i])
      numaxlen += cnt[i];
  };
  return numaxlen;
}

// https://leetcode.com/problems/subarray-sum-equals-k/description/
int subarraySum(vector<int>& nums, int k)
{
  int cum = 0; // cumulated sum
  int vsize = nums.size();
  unordered_map<int, int> rec; // prefix sum recorder
  int cnt = 0; // number of found subarray
  rec[0]++; // to take into account those subarrays that begin with index 0
  for (int i = 0; i < vsize; i++)
  {
    cum += nums[i];
    cnt += rec[cum - k];
    rec[cum]++;
  }
  return cnt;
}

// https://leetcode.com/problems/continuous-subarray-sum/description/
bool checkSubarraySum(vector<int>& nums, int k)
{
  int n = nums.size(), sum = 0, pre = 0;
  unordered_set<int> modk;
  for (int i = 0; i < n; ++i)
  {
    sum += nums[i];
    int mod = k == 0 ? sum : sum % k;
    if (modk.count(mod))
      return true;
    modk.insert(pre);
    pre = mod;
  }
  return false;
}

/*
 https://leetcode.com/problems/subarray-product-less-than-k/description/

 Your are given an array of positive integers nums.
 Count and print the number of (contiguous) subarrays
 where the product of all the elements in the subarray is less than k.

 Example 1:
 Input: nums = [10, 5, 2, 6], k = 100
 Output: 8
 Explanation: The 8 subarrays that have product less than 100 are:
 [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
 Note that [10, 5, 2] is not included as the product of 100
 is not strictly less than k.

 Note:
 0 < nums.length <= 50000.
 0 < nums[i] < 1000.
 0 <= k < 10^6.
 */
int numSubarrayProductLessThanK(vector<int>& nums, int k)
{
  if (k == 0)
    return 0;
  int cnt = 0;
  int pro = 1;
  int vsize = (int) nums.size();
  for (int i = 0, j = 0; j < vsize; j++)
  {
    pro *= nums[j];
    while (i <= j && pro >= k)
    {
      pro /= nums[i++];
    }
    cnt += j - i + 1;
  }
  return cnt;
}

/*
 Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i;
 and a non-negative integer fee representing a transaction fee.
 You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.
 You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)
 Return the maximum profit you can make.

 Example 1:
 Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
 Output: 8

 Explanation: The maximum profit can be achieved by:
 Buying at prices[0] = 1
 Selling at prices[3] = 8
 Buying at prices[4] = 4
 Selling at prices[5] = 9
 The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

 Note:
 0 < prices.length <= 50000.
 0 < prices[i] < 50000.
 0 <= fee < 50000.

 */
int maxProfit_iii(vector<int>& prices, int fee)
{
  int s0 = 0, s1 = INT32_MIN;
  for (int p : prices)
  {
    cout << p << endl;
    int tmp = s0;
    s0 = max(s0, s1 + p);
    cout << tmp << endl;
    cout << s1 << "+" << p << "=" << s0 << endl;
    s1 = max(s1, tmp - p - fee);
    cout << tmp << "-" << p << "-" << fee << "=" << s1 << endl << endl;
  }
  return s0;
}

/*
 "00:01:07,400-234-090
 00:05:01,701-080-080
 00:05:00,400-234-090"
 * */
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim))
  {
    *(result++) = item;
  }
}

std::vector<std::string> split(const std::string &s, char delim)
{
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

int sig_codility_q1(string &S)
{
  unordered_map<int, std::pair<int, int>> logs;
  std::vector<std::string> entries = split(S, '\n');
  std::string time;
  std::string num;
  std::string phonenum;
  std::vector<std::string> entrystr;
  std::vector<std::string> timestrs;
  int digitalphonenum;
  for (auto& entry : entries)
  {
    time.clear();
    num.clear();
    phonenum.clear();
    entrystr = split(entry, ',');
    time = std::move(entrystr[0]);
    num = std::move(entrystr[1]);
    auto numstrs = split(num, '-');
    for (auto& num : numstrs)
      phonenum += num;
    digitalphonenum = atoi(phonenum.c_str());
    cout << digitalphonenum << endl;
    timestrs = split(time, ':');
    int h2s = (atoi(string(1, timestrs[0][0]).c_str()) * 10 + atoi(string(1, timestrs[0][1]).c_str())) * 60 * 60;
    int m2s = (atoi(string(1, timestrs[1][0]).c_str()) * 10 + atoi(string(1, timestrs[1][1]).c_str())) * 60;
    int s = (atoi(string(1, timestrs[2][0]).c_str()) * 10 + atoi(string(1, timestrs[2][1]).c_str()));
    int sumup = h2s + m2s + s;
    logs[digitalphonenum].first += sumup;
    int totalfee = 3 * sumup;
    if (sumup >= 5 * 60)
    {
      if (s > 0)
      {
        s = 0;
        m2s += 60;
      }
      sumup = (h2s + m2s + s) / 60;
      totalfee = 150 * sumup;
    }
    logs[digitalphonenum].second += totalfee;
  }
  int fee = 0;
  int longest = 0;
  int minphonenum = INT32_MAX;
  for (auto& entry : logs)
  {
    cout << entry.first << " t" << entry.second.first << " c" << entry.second.second << endl;
    if (entry.second.first > longest)
      longest = entry.second.first;
    fee += entry.second.second;
  }
  for (auto& entry : logs)
  {
    if (entry.second.first == longest)
    {
      if (entry.first < minphonenum)
        minphonenum = entry.first;
    }
  }
  fee -= logs[minphonenum].second;
  cout << "smallest_num: " << minphonenum << " longest: " << longest << "fee: " << fee << endl;
  return fee;
}

#include <iostream>
using namespace std;

/*AKUNA CAPITAL Quantitative Developer Interview Questions*/
//  Q1: 9 Feb 2018 Junior Developer (C++) Interview
// Several APIs are given. You're asked to write two functions to
// compute round-trip time between two clients in a network.
// Solution:
#include <cstring>
//#include <arpa/inet.h>
//#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>
// 1. use udp instead of tcp due to tcp's ack mecnism
// 1234 where 1 is missing, 234 recived but hold in receiver buf
// but they are not delivered to user layer which cause round time
// measurement inaccurate.
// 2. as udp is unreliable so we assign every packet a unique number
// as its indentity, remeber sent time and when receiving the a packet,
// unpack the number and use this number to find the againest sent time
// do substact of the senttiem with received time. accumulate it to toal time intervals.

//  Q2:10 Sep 2017 Junior Quantitative Developer Interview
//1) Enter a dimension(number) and verify if it can be a 3 dimensional figure (minimum dimension is 2)
//Eg. if you enter 8 -> (2 x 2 x 2) -> Yes
//10 -> (5x2) -> No
//12 -> (2x2x3) -> Yes
// Solution:
static bool is_3_dimention_prime_fac(int n)
{
  int c = 1;
  int z = 2;
  while (z * z <= n)
  {
    if (n % z == 0)
    {
      n /= z;
      c++;
      if (c == 3)
        return true;
    }
    else
      z++;
  }
  return false;
}

// 18 May 2018  Quantitative Developer Interview
// had to sort numbers in an array that appeared numerous times
// and output them so that they  only appeared once:
// input -> [0001123333] output -> [0123]
// Solution:
static void appear_once(int nums[], int size)
{
  int p = 0;
  for (int i = 1; i < size; i++)
  {
    if (nums[i] != nums[i - 1])
    {
      if (i - p > 1)
        nums[p + 1] = nums[i];
      p = i;
    }
  }
}

// 5 Nov 2017 
// 1. Given a list of numbers with some repeated elements, return a new list that every
// element appears only once.For example, input list : [1, 2, 2, 3, 4, 4], output : [1, 2, 3, 4].
// S:  unordered_map
//2. Return the powers of 2 in the inclusive range[low, high]('low', 'high' are positive integers).
// S: loop each element if(n & (n-1) == 0)->it is power of 2

// 29 Jun 2016 
// Unusual sort: sort an array A such that: A[0]<A[1]>A[2]<A[3]>A[4]<A[5].............
// S:    
//void wiggleSort(vector<int>& nums)
//{
//	int flag = 1;
//	for (int i = 1; i < nums.size(); ++i)
//	{
//		if (nums[i] * flag < nums[i - 1] * flag)
//			swap(nums[i], nums[i - 1]);
//		flag = -flag;
//	}
//}

// 28 Feb 2016
// 1 Find largest products of two numbers from an array 
// S: int first_two_min_negative_nums[2]; int first_two_max_positive_nums[2];
// 2 Remove duplicates of an array  S: hashmap
// 3 Two sum S: hashmap
// number of bit 1 in a number S: sizeof(num)*8  while shift right anf then and 0x01

// 4 Nov 2015
// Why might multiple threads calling a simple function involving array access / possible modification
// be much slower than a single thread calling a function ?
// S: cache coherence 

// 7 Apr 2017
// 1. Implement a thread safe circular buffer
// 2. There are N satellites that can deliver messages.Each  satellite can only 
// deliver messages to some subset of satellites.For each satellite that can 
// send a message, each message has a delay in time.Given a starting satellite,
// that sends a message return the minimum time required for all the satellites 
// to receive the message.If the message cannot be broadcasted to all satellites
// then return -1.
// Solution:

// Circular buffer  fifo no lock impl

namespace _3_shared_data_protection
{
  namespace thread_safe_stack
  {
    /**
     * here is my way to prevent interface arised race condition
     * just lock the code sections that use the shared data with
     *  same mutex locker
     */
    stack<vector<int>> data;
    mutex m;
    // some threads execute pop_stack
    void pop_stack(vector<int>& v)
    {
      lock_guard<mutex> lock(m);
      if (!data.empty())
      {
        v = std::move(data.top());
        data.pop();
      }
    }
    // some threads execute push_stack
    void push_stack()
    {
      lock_guard<mutex> lock(m);
      data.push( { 1, 2, 3 });
    }

    /** ?????
     * here is book's way to prevent interface arised race condition
     * if using empty() why check emty() again in pop();
     * the invariant here is that if not empty i must pop i must use the poped
     * value to do something before i release the locker ?
     */
    template<typename T>
    class thr_safe_stack
    {
      private:
        stack<T> data;
        mutable mutex lock;
      public:
        thr_safe_stack(const thr_safe_stack& other)
        {
          lock_guard<mutex> lock(other.lock);
          data = other.data;
        }
        thr_safe_stack(thr_safe_stack&& other)
        {
          lock_guard<mutex> lock(other.lock);
          data = std::move(other.data);
        }
        thr_safe_stack& operator=(const thr_safe_stack& other)
        {
          // deaklock can happen in this method
          // in order to thread-safe assign other to this
          // we need to lock both of thr_safe_stack instances this and other.
          // thread A  has locked other locker
          // (which is actually this instance  of thead B )
          // thread B  has locked other locker
          // (which is actually this instance  of thead A )
          // we have:
          // other locked                    this locked
          // thread A is                       thread B is
          // waiting                              waiting
          // this unlcoked by B         other unlocked by A  --> dead lock !!!
          // this locked                        other locked

          // Solution 1: always lock mutexes in same order
          lock_guard<mutex> lockother(other.lock);
          lock_guard<mutex> lockthis(this->lock);
          return *this;
        }
        thr_safe_stack& operator=(thr_safe_stack&&) = delete;
        shared_ptr<T> pop()
        {
          lock_guard<mutex> lock(this->lock);
          if (data.empty())
            return nullptr;
          shared_ptr<T> const res(make_shared<T>(std::move(data.top())));
          data.pop();
          return res;
        }
        void pop(T& value)
        {
          lock_guard<mutex> lock(this->lock);
          if (data.empty())
            return;
          value = std::move(data.top());
          data.pop();
        }
        bool empty()
        {
          lock_guard<mutex> lock(this->lock);
          return data.empty();
        }
    };
  }
}
namespace Cache_coherence
{
/**
 https://cs.stackexchange.com/questions/20044/memory-consistency-vs-cache-coherence
 https://en.wikipedia.org/wiki/Cache_coherence

 My understandings:
 this make sure sequencial consistency available in mutiprocessor systems by soving out delays between
 different reads/writes operations to a single memory location that mabe performed on multi threads
 in any order (due to nature of race codition of multi threads ).

 There are many writes and many reads interlevely by many threads in store-load-sequence,
 the write and read order is detemrined by race codition (who runs first, who runs secondly).

 see store-load-sequence below:
 ...s0...s1...l1...s2...l2...
 if trsaction serilization enabled:
 the thread of l1 must see 0 ---> 1,  load value 1 eventually in this case
 the thread of l2 must see 0 ---> 1 ---> 2,  load value 2 eventually  in this case
 the thread of l2 must see 0 ---> 1 ---> 2,  load value 2 eventually  in this case
 else:
 the thread of l1 may see unordered sequence 1 ---> 0,             load value 0 eventually  in this case
 the thread of l2 may see unordered sequence 0 ---> 2 ---> 1,  load value 1 eventually in this case ()
 the thread of l2 may see ordered sequence      0 ---> 1 ---> 2,  load value 2 eventually in this case

 sequencial consistency must be meory cohernce but the reversed is not true.
 initially int a =0, b = 0
 t1 stores 1 to a
 t1 stores 1 to b
 t3 loads a;
 t4 loads b;
 if it is memory cohence:
 t1 stores 1 to b (b=1)
 t3 loads a  (a= 0)
 t1 stores 1 to a (a=1)
 t3 loads b (b=1)

 if it is sequencial consistency:
 t1 stores 1 to a (a=1)
 t1 stores 1 to b (b=1)
 t4 loads b; (b=1)
 t3 loads a; (a=1)
 */
}
namespace aligns_test
{
  struct alignas(64) spsc_queue
  {
      alignas(64)
      atomic<size_t> write_index_;alignas(64)
      atomic<size_t> read_index_;
      int hello(int)
      {
        return 0;
      }
  };

  void run()
  {
    // getconf LEVEL1_DCACHE_LINESIZE usually it is 64bytes
    spsc_queue s;
    cout << "sizeof(S): " << sizeof(spsc_queue) << ", aligned to 64: " << (((uintptr_t) &s) & 63) << endl;
    int (spsc_queue::*sp)(int) = &spsc_queue::hello;
    (s.*sp)(12);
    spsc_queue* sptr = &s;
    (sptr->*sp)(12);
  }
}

namespace virtual_methods_table
{
// 基类
  class Base
  {
    public:
      virtual void Fun1()
      {
        cout << "Base::Fun1" << endl;
      }
      virtual void Fun2()
      {
        cout << "Base::Fun2" << endl;
      }
      virtual void Fun3()
      {
        cout << "Base::Fun3" << endl;
      }
      virtual ~Base()
      {
      }
    private:

  };

// 无重载继承类
  class Derive: Base
  {
    public:
      virtual void DeriveFun1()
      {
        cout << "Derive::Fun1" << endl;
      }
      virtual void DeriveFun2()
      {
        cout << "Derive::Fun2" << endl;
      }
      virtual void DeriveFun3()
      {
        cout << "Derive::Fun3" << endl;
      }
  };

// 重载继承类
  class Override: public Base
  {
    public:
      virtual void Fun1()
      {
        cout << "Override::Fun1" << endl;
      }
      virtual void OverrideFun2()
      {
        cout << "Override::Fun2" << endl;
      }
      virtual void OverrideFun3()
      {
        cout << "Override::Fun3" << endl;
      }
  };

// 多重继承无重载
  class Base1
  {
    public:
      virtual void Fun1()
      {
        cout << "Base1::Fun1" << endl;
      }
      virtual void Fun2()
      {
        cout << "Base1::Fun2" << endl;
      }
      virtual void Fun3()
      {
        cout << "Base1::Fun3" << endl;
      }
      virtual ~Base1()
      {
      }
  };
  class Base2
  {
    public:
      virtual void Fun1()
      {
        cout << "Base2::Fun1" << endl;
      }
      virtual void Fun2()
      {
        cout << "Base2::Fun2" << endl;
      }
      virtual void Fun3()
      {
        cout << "Base2::Fun3" << endl;
      }
      virtual ~Base2()
      {
      }
  };
  class MultipleDerive: public Base, public Base1, public Base2
  {
    public:
      virtual void MultipleDeriveFun1()
      {
        cout << "MultipleDerive::Fun1" << endl;
      }
      virtual void MultipleDeriveFun2()
      {
        cout << "MultipleDerive::Fun2" << endl;
      }
      virtual void MultipleDeriveFun3()
      {
        cout << "MultipleDerive::Fun3" << endl;
      }
  };

  // 多重继承重载
  class MultipleDeriveOverride: public Base, public Base1, public Base2
  {
    public:
      virtual void Fun1()
      {
        cout << "MultipleDerive::Fun1" << endl;
      }
      virtual void MultipleDeriveFun2()
      {
        cout << "MultipleDerive::Fun2" << endl;
      }
      virtual void MultipleDeriveFun3()
      {
        cout << "MultipleDerive::Fun3" << endl;
      }
  };

  // 公有继承访问父类非公有虚函数
  class Base3
  {
    private:
      virtual void Fun1()
      {
        cout << "Base3::Fun1" << endl;
      }
    public:
      virtual ~Base3()
      {
      }
  };
  class Derive1: public Base3
  {
  };
  typedef void (*Fun)(void);

  void Sub_7()
  {
    Derive1 v1;
    Fun pFun = (Fun) *((int*) *(int*) (&v1) + 0);
    pFun();
  }
  void Sub_6()
  {
    Base *v1 = new Override();
    // 多态
    v1->Fun1();
    Fun pFun = NULL;
    //pFun = (Fun)*((Override*)(v1));
    pFun();
  }
  void Sub_5()
  {
    MultipleDeriveOverride v1;
    Fun pFun = NULL;
    Base *b = &v1;
    Base1 *b1 = &v1;
    Base2 *b2 = &v1;
    b->Fun1();
    b->Fun2();
    b->Fun3();
    b1->Fun1();
    b1->Fun2();
    b1->Fun3();
    b2->Fun1();
    b2->Fun2();
    b2->Fun3();
  }
  void Sub_4()
  {
    MultipleDerive v1;
    Fun pFun = NULL;
    int** pVtable = (int**) &v1;
    // Base的第一函数
    pFun = (Fun) pVtable[0][0];
    pFun();
    // Base的第二函数
    pFun = (Fun) pVtable[0][1];
    pFun();
    // Base的第三函数
    pFun = (Fun) pVtable[0][2];
    pFun();
    // 继承类的第一函数
    pFun = (Fun) pVtable[0][3];
    pFun();
    // 继承类的第二函数
    pFun = (Fun) pVtable[0][4];
    pFun();
    // 继承类的第三函数
    pFun = (Fun) pVtable[0][5];
    pFun();
    // Base1的第一函数
    pFun = (Fun) pVtable[1][0];
    pFun();
    // Base1的第二函数
    pFun = (Fun) pVtable[1][1];
    pFun();
    // Base1的第三函数
    pFun = (Fun) pVtable[1][2];
    pFun();
    // Base2的第一函数
    pFun = (Fun) pVtable[2][0];
    pFun();
    // Base2的第二函数
    pFun = (Fun) pVtable[2][1];
    pFun();
    // Base2的第三函数
    pFun = (Fun) pVtable[2][2];
    pFun();
  }
  void Sub_3()
  {
    Override v1;
    Fun pFun = NULL;
    // 运行重载第一函数
    pFun = (Fun) *((int*) *(int*) (&v1));
    pFun();
    // 运行父类第二函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 1);
    pFun();
    // 运行父类第三函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 2);
    pFun();
    // 运行重载第二函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 3);
    pFun();
    // 运行重载第三函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 4);
    pFun();
  }
  void Sub_2()
  {
    Derive v1;
    Fun pFun = NULL;
    // 运行父类第一函数
    pFun = (Fun) *((int*) *(int*) (&v1));
    pFun();
    // 运行父类第二函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 1);
    pFun();
    // 运行父类第三函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 2);
    pFun();
    // 运行子类第一函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 3);
    pFun();
    // 运行子类第二函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 4);
    pFun();
    // 运行子类第三函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 5);
    pFun();
  }
  void Sub_1()
  {
    Base v1;
    int* vt = reinterpret_cast<int*>(*((int*) &v1));
    Fun pFun = NULL;
    cout << "虚函数表地址：" << (int*) (&v1) << endl;
    cout << "虚函数表第一函数地址：" << (int*) *(int*) (&v1) << endl;
    // 运行第一个函数
    pFun = (Fun) *((int*) *(int*) (&v1));
    pFun();
    // 运行第二个函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 1);
    pFun();
    // 运行第三个函数
    pFun = (Fun) *((int*) *(int*) (&v1) + 2);
    pFun();
    // 虚函数表的结束
    cout << ((&v1) + 3) << endl;
  }

  void run()
  {
    // 验证虚函数表
    //Sub_1();
    // 验证无虚函数覆盖的一般继承
    Sub_2();
    // 验证虚函数重载父类的虚表
    Sub_3();
    // 验证多重继承无重载的虚表
    //Sub_4();
    // 验证多重继承有重载的虚表
    //Sub_5();
    // 验证父类指针访问子类自己的虚函数??
    //Sub_6();
    // 验证公有继承访问父类非公有虚函数
    //Sub_7();
  }
}
namespace _5_2_reading_and_writing_variables_from_different_threads
{
  /**
   Suppose you have two threads, one of which is populating a data structure to be read
   by the second. In order to avoid a problematic race condition, the first thread sets a
   flag to indicate that the data is ready, and the second thread doesn’t read the data
   until the flag is set. The following listing shows such a scenario.
   */
  vector<int> data;
  atomic<bool> data_ready(false);
  void reader_thread()
  {
    while (!data_ready.load())
      this_thread::sleep_for(chrono::milliseconds(1));
    cout << "answer = " << data[0] << endl;
  }
  void writer_thread()
  {
    data.push_back(42);
    data_ready = true;
  }
}

namespace round_robin
{
  void simulate()
  {
    printf("total processes:\t ");
    int process_num;
    scanf("%d", &process_num);
    int remain_process_num = process_num;

    int* arrive_times = new int[process_num];
    int* wait_times = new int[process_num];
    int* burst_times = new int[process_num];
    int* turnaround_times = new int[process_num];
    int* remain_burst_times = new int[process_num];
    int count = 0;
    for (; count < process_num; count++)
    {
      printf("Enter arrival time and burst time for the processes %d : ", count);
      scanf("%d", &arrive_times[count]);
      scanf("%d", &burst_times[count]);
      remain_burst_times[count] = burst_times[count];
      wait_times[count] = 0;
      turnaround_times[count] = 0;
    }

    printf("Enter Time Slice:\t");
    int time_slice;
    scanf("%d", &time_slice);

    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
    bool completed = false;
    for (int time = 0, count = 0; remain_process_num != 0;)
    {
      if (remain_burst_times[count] <= time_slice && remain_burst_times[count] > 0)
      {
        time += remain_burst_times[count];
        remain_burst_times[count] = 0;
        completed = true;
      }
      else if (remain_burst_times[count] > 0)
      {
        time += time_slice;
        remain_burst_times[count] -= time_slice;
      }
      if (remain_burst_times[count] == 0 && completed)
      {
        remain_process_num--;
        wait_times[count] = time - arrive_times[count] - burst_times[count];
      }
    }
  }
}

int main()
{

  //aligns_test::run();
  virtual_methods_table::run();
  //cout << "sig_codility_q1:" << endl;
  //string logs = "00:05:00,701-080-080\n"
  //	"00:05:00,400-234-090";
  //cout << sig_codility_q1(logs);

  //vector<int> vec_two_sum{ 0, 0, 3, 4 };
  //int target_two_sum = 0;
  //vector<int> ret_two_sum = twoSum(vec_two_sum, target_two_sum);
  //std::cout << "\ntwo_sum_ret: ";
  //for (size_t i = 0; i < ret_two_sum.size(); i++)
  //	std::cout << ret_two_sum[i] << " ";
  //std::cout << endl;

  //vector<int> two_sum_sorted_array{ 0, 0, 3, 4 };
  //int two_sum_sorted_target = 0;
  //vector<int> two_sum_sorted_ret = twoSumSorted(two_sum_sorted_array, two_sum_sorted_target);
  //std::cout << "two_sum_sorted_ret: ";
  //for (size_t i = 0; i < two_sum_sorted_ret.size(); i++)
  //	std::cout << two_sum_sorted_ret[i] << " ";
  //std::cout << endl;

  //vector<vector<int> > sum3_ret;
  //vector<int> sum3_iput{ -2, 0, 1, 1, 2 }; //-2 -2 -2  0000 111  2222
  //sum3_ret = threeSum(sum3_iput);
  //std::cout << "three_sum_ret: ";
  //if (sum3_ret.empty())
  //	cout << "[]";
  //else
  //	for (int i = 0; i < (int)sum3_ret.size(); i++)
  //	{
  //		cout << "[";
  //		for (int ii = 0; ii < (int)sum3_ret[i].size(); ii++)
  //		{
  //			cout << sum3_ret[i][ii] << ", ";
  //		}
  //		cout << "], ";
  //	}

  //int sum3_closeast_ret;
  //vector<int> sum3_closeast_array{ -4, -1, 1, 2 };
  //int sum3_closeast_tartget = 1;
  //sum3_closeast_ret = threeSumClosest(sum3_closeast_array, sum3_closeast_tartget);
  //cout << "\nsum3_closeast_ret: " << sum3_closeast_ret << endl;

  //vector<int> remove_duplicates_array{ 1, 1, 2 };
  //int remove_duplicates_ret = removeDuplicates(remove_duplicates_array);
  //std::cout << "remove_duplicates_ret: " << remove_duplicates_ret << ", array: ";
  //for (int i = 0; i < remove_duplicates_ret; i++)
  //	std::cout << remove_duplicates_array[i] << " ";
  //std::cout << endl;

  //vector<int> remove_element_array{ 1, 1, 1, 0, 1, 1, 0 };
  //int removing_element = 1;
  //int remove_element_ret = removeElement(remove_element_array, removing_element);
  //std::cout << "remove_element_ret: " << remove_element_ret << ", array: ";
  //for (int i = 0; i < remove_element_ret; i++)
  //	std::cout << remove_element_array[i] << " ";
  //std::cout << endl;

  //vector<int> findDisappearedNumbers_array{ 4, 3, 2, 7, 8, 2, 3, 1 };
  //vector<int> findDisappearedNumbers_ret = findDisappearedNumbers(findDisappearedNumbers_array);
  //std::cout << "findDisappearedNumbers_ret: ";
  //for (int i = 0; i < (int)findDisappearedNumbers_ret.size(); i++)
  //	std::cout << findDisappearedNumbers_ret[i] << " ";
  //std::cout << endl;

  //vector<int> array_rotate_array{ 1, 2, 3, 4, 5, 6, 7 };
  //int k = 4;
  //array_rotate(array_rotate_array, k);
  //std::cout << "array_rotate_array_ret: ";
  //for (int i = 0; i < (int)array_rotate_array.size(); i++)
  //	std::cout << array_rotate_array[i] << " ";
  //std::cout << endl;

  //string s = "()[]";
  //cout << "isValid ret: ";
  //cout << isValid(s) << endl;

  //vector<int> array_maxProduct{ 2, };
  //std::cout << "maxProduct: ";
  //int ret_maxProduct = maxProduct(array_maxProduct);
  //std::cout << ret_maxProduct << endl;

  //vector<int> array_maxProfit{ 7, 6, 4, 3, 1 };
  //std::cout << "maxProfit: ";
  //int ret_maxProfit = maxProfit_i(array_maxProfit);
  //std::cout << ret_maxProfit << endl;

  //vector<int> array_maxProfit_ii{ 7, 6, 4, 3, 1 };
  //std::cout << "maxProfit_ii: ";
  //int ret_maxProfit_ii = maxProfit_ii(array_maxProfit_ii);
  //std::cout << ret_maxProfit_ii << endl;

  //// 1, 3, 7, 5, 10, 3  k3 p6
  //// 1, 3, 2,8,4,9 k3 p6
  //// 1,5,9 k3 p5
  //// 1, 2 k3 p0

  //vector<int> array_maxProfit_iii{ 1, 3, 2, 8, 4, 9 };
  //int fee_maxProfit_iii = 1;
  //std::cout << "maxProfit_iii: ";
  //int ret_maxProfit_iii = maxProfit_iii(array_maxProfit_iii, fee_maxProfit_iii);
  //std::cout << ret_maxProfit_iii << endl;

  //vector<int> array_findNumberOfLIS{ 1, 2, 4, 3, 5, 4, 7, 2 };
  //std::cout << "findNumberOfLIS: ";
  //int ret_findNumberOfLIS = findNumberOfLIS(array_findNumberOfLIS);
  //std::cout << ret_findNumberOfLIS << endl;

  //floyd_main();

  union
  {
      struct
      {
          char a :1;
          char b :2;
          char c :3;
      } d;
      char e;
  } f;
  f.e = 1;
  printf("%d\n", f.d.a);

  return 0;
}
