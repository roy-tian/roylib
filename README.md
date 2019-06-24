<table>
  <tr>
    <th></th>
    <th colspan="2">STATIC LINEAR LISTS</th>
    <th colspan="3">LINKED LINEAR LISTS</th>
    <th colspan="4">BINARY TREES</th>
    <th colspan="3">ADAPTERS</th>
    <th></th>
  </tr>
  <tr>
    <td></td>
    <td><strong><code>RoyArray</code></strong></td>
    <td><strong><code>RoyVector</code></strong></td>
    <td><strong><code>RoySList</code></strong></td>
    <td><strong><code>RoyList</code></strong></td>
    <td><strong><code>RoyDeque</code></td>
    <td><strong><code>RoySet</code></strong></td>
    <td><strong><code>RoyMSet</code></strong></td>
    <td><strong><code>RoyMap</code></strong></td>
    <td><strong><code>RoyMMap</code></strong></td>
    <td><strong><code>RoyStack</code></strong></td>
    <td><strong><code>RoyQueue</code></strong></td>
    <td><strong><code>RoyHeap</code></strong></td>
    <td></td>
  </tr>

  <tr>
    <td rowspan="2">CONSTRUCTORS</td>
    <td><code>new</code></td>
    <td><code>new</code></td>
    <td><code>new</code></td>
    <td><code>new</code></td>
    <td><code>new</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>new</code></td>
    <td><code>new</code></td>
    <td></td>
    <td rowspan="2">CONSTRUCTORS</td>
  </tr>

  <tr>
    <td><code>delete</code></td>
    <td><code>delete</code></td>
    <td><code>delete</code></td>
    <td><code>delete</code></td>
    <td><code>delete</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>delete</code></td>
    <td><code>delete</code></td>
    <td></td>
  </tr>

  <tr>
    <td rowspan="10">POINTERS /<br>ITERATORS</td>
    <td><code>pointer</code></td>
    <td><code>pointer</code></td>
    <td></td>
    <td><code>iterator</code></td>
    <td><code>pointer</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td rowspan="10">POINTERS /<br>ITERATORS</td>
  </tr>

  <tr>
    <td><code>const_pointer</code></td>
    <td><code>const_pointer</code></td>
    <td></td>
    <td><code>const_iterator</code></td>
    <td><code>const_pointer</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td><code>reverse_iterator</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td><code>const_reverse_iterator</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td><code>element</code></td>
    <td><code>element</code></td>
    <td></td>
    <td><code>element</code></td>
    <td><code>element</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td><code>at</code></td>
    <td><code>at</code></td>
    <td></td>
    <td><code>at</code></td>
    <td><code>at</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td><code>front</code></td>
    <td><code>begin</code></td>
    <td><code>begin</code></td>
    <td><code>front</code></td>
    <td><code>min</code></td>
    <td><code>min</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td><code>cbegin</code></td>
    <td><code>cbegin</code></td>
    <td><code>const_front</code></td>
    <td><code>const_min</code></td>
    <td><code>const_min</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>
  
  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td><code>rbegin</code></td>
    <td><code>back</code></td>
    <td><code>max</code></td>
    <td><code>max</code></td>
    <td></td>
    <td></td>
    <td><code>top</code></td>
    <td><code>back</code></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td><code>crbegin</code></td>
    <td><code>const_back</code></td>
    <td><code>const_max</code></td>
    <td><code>const_max</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td rowspan="4">CAPACITY</td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td><code>size</code></td>
    <td rowspan="4">CAPACITY</td>
  </tr>

  <tr>
    <td><code>capacity</code></td>
    <td><code>capacity</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>capacity</code></td>
    <td><code>capacity</code></td>
    <td></td>
  </tr>

  <tr>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
    <td><code>empty</code></td>
  </tr>

  <tr>
    <td><code>full</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>full</code></td>
    <td><code>full</code></td>
    <td></td>
  </tr>

  <tr>
    <td rowspan="10">MOLDIFIERS</td>
    <td><code>insert</code></td>
    <td><code>insert</code></td>
    <td></td>
    <td><code>insert</code></td>
    <td><code>insert</code></td>
    <td><code>insert</code></td>
    <td><code>insert</code></td>
    <td><code>insert</code></td>
    <td><code>insert</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td rowspan="10">MOLDIFIERS</td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td><code>insert_reverse</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td><code>push_front</code></td>
    <td><code>push_front</code></td>
    <td><code>push_front</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>push</code></td>
  </tr>

  <tr>
    <td><code>push_back</code></td>
    <td><code>push_back</code></td>
    <td></td>
    <td><code>push_back</code></td>
    <td><code>push_back</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>push</code></td>
    <td><code>push</code></td>
    <td></td>
  </tr>

  <tr>
    <td><code>erase</code></td>
    <td><code>erase</code></td>
    <td></td>
    <td><code>erase</code></td>
    <td><code>erase</code></td>
    <td><code>erase</code></td>
    <td><code>erase</code></td>
    <td><code>erase</code></td>
    <td><code>erase</code></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td></td>
    <td><code>erase_reverse</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td><code>erase_fast</code></td>
    <td><code>erase_fast</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td><code>pop_front</code></td>
    <td><code>pop_front</code></td>
    <td><code>pop_front</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>pop</code></td>
    <td><code>pop</code></td>
  </tr>

  <tr>
    <td><code>pop_back</code></td>
    <td><code>pop_back</code></td>
    <td></td>
    <td><code>pop_back</code></td>
    <td><code>pop_back</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td><code>pop</code></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td><code>clear</code></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td rowspan="5">LIST<br>OPERATIONS</td>
    <td></td>
    <td></td>
    <td><code>merge</code></td>
    <td><code>merge</code></td>
    <td><code>merge</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td rowspan="5">LIST<br>OPERATIONS</td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td><code>remove_if</code></td>
    <td><code>remove_if</code></td>
    <td><code>remove_if</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td><code>reverse</code></td>
    <td><code>reverse</code></td>
    <td><code>reverse</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td><code>unique</code></td>
    <td><code>unique</code></td>
    <td><code>unique</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td></td>
    <td><code>sort</code></td>
    <td><code>sort</code></td>
    <td><code>sort</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td rowspan="2">TRAVERSERS</td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td><code>for_each</code></td>
    <td></td>
    <td></td>
    <td></td>
    <td rowspan="2">TRAVERSERS</td>
  </tr>

  <tr>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td><code>for_which</code></td>
    <td></td>
    <td></td>
    <td></td>
  </tr>

  <tr>
    <td></td>
    <td><strong><code>RoyArray</code></strong></td>
    <td><strong><code>RoyVector</code></strong></td>
    <td><strong><code>RoySList</code></strong></td>
    <td><strong><code>RoyList</code></strong></td>
    <td><strong><code>RoyDeque</code></td>
    <td><strong><code>RoySet</code></strong></td>
    <td><strong><code>RoyMSet</code></strong></td>
    <td><strong><code>RoyMap</code></strong></td>
    <td><strong><code>RoyMMap</code></strong></td>
    <td><strong><code>RoyStack</code></strong></td>
    <td><strong><code>RoyQueue</code></strong></td>
    <td><strong><code>RoyHeap</code></strong></td>
    <td></td>
  </tr>

  <tr>
    <th></th>
    <th colspan="2">STATIC LINEAR LISTS</th>
    <th colspan="3">LINKED LINEAR LISTS</th>
    <th colspan="4">BINARY TREES</th>
    <th colspan="3">ADAPTERS</th>
    <th></th>
  </tr>
</table>

