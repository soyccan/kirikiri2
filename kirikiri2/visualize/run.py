import webweb
import os
import re
import collections
import numpy
import pdb
import sys
import traceback


class CounterMap(dict):
    def __init__(self):
        super().__init__()
        self.revmap = {}

    def __getitem__(self, key):
        if key not in self:
            value = len(self)
            print('new key:', key, value)
            self[key] = value
            self.revmap[value] = key
            return value
        else:
            print('existing key', key, self.get(key))
            return self.get(key)


try:
    #  hash_table = {}
    #  rev_hash_table = {}
    #  hash_counter = 0
    edges = []
    hash_table = CounterMap()
    cpp = []
    G = collections.defaultdict(list)

    # Set the directory you want to start from
    for dirName, subdirList, fileList in os.walk('../src'):
        print('Found directory: %s' % dirName)
        for fname in fileList:
            if (fname.endswith('.cpp')
                    or fname.endswith('.h')):
                print('\t%s' % fname)

                dep_list = [
                    re.search(b'^#include "(.*?)"', ln)
                    for ln in open(dirName + '/' + fname, 'rb')
                    if ln.startswith(b'#include "')]
                dep_list = [x.group(1).decode() for x in dep_list if x]
                print('\t', dep_list)

                c = hash_table[fname]
                assert c != None
                #  if not c:
                #      c = hash_table[fname] = hash_counter
                #      rev_hash_table[hash_counter] = {'name': fname}
                #      hash_counter += 1

                for dep in dep_list:
                    h = hash_table[dep]
                    assert h != None
                    #  if not h:
                    #      h = hash_table[dep] = hash_counter
                    #      rev_hash_table[hash_counter] = {'name': dep}
                    #      hash_counter += 1

                    edges.append((c, h))
                    G[c].append(h)

                if fname.endswith('.cpp') and 'src/plugins' not in fname:
                    cpp.append(c)

    V = len(hash_table)
    #  G = numpy.zeros((V, V), dtype=bool)
    #  for i in range(V):
    #      G[i][i] = True
    #  for i, j in edges:
    #      G[i][j] = True
    #  for k in range(V):
    #      print('k=', k)
    #      for i in range(V):
    #          for j in range(V):
    #              G[i][j] = G[i][j] or (G[i][k] and G[k][j])

    ref = collections.defaultdict(list)
    vis = numpy.zeros(V, dtype=bool)

    def dfs(u, root):
        for v in G[u]:
            print(u, v, hash_table.revmap[u], hash_table.revmap[v])
            if not vis[v]:
                vis[v] = True
                ref[v].append(root)
                dfs(v, root)

    for i in cpp:
        if hash_table.revmap[i] != 'XP3Archive.cpp':
            continue
        vis.fill(False)
        dfs(i, i)

    #  for j in range(V):
    #      for i in range(V):
    #          if i in cpp and G[i][j]:
    #              reachability[j] += 1
    #  reachability = []
    #  for j in range(V):
    #      if j not in cpp:
    #          reachability.append((ref[j], hash_table.revmap[j]))
    reachability = list(ref.items())
    reachability.sort(key=lambda x: len(x[1]))
    for x, y in reachability:
        print(hash_table.revmap[x], len(set(y)))
        print(list(map(lambda x: hash_table.revmap[x], set(y))))
        print()

    #  web = webweb.Web(
    #      adjacency=edges,
    #      display={'nodes': rev_hash_table},
    #  )
    #  web.show()

except:
    extype, value, tb = sys.exc_info()
    traceback.print_exc()
    pdb.post_mortem(tb)
