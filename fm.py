import networkx as nx
from networkx.drawing.nx_agraph import write_dot, graphviz_layout
import re,os,numpy as np,matplotlib.pyplot as plt
from pycparser import c_parser, c_ast, parse_file, c_generator

filename = 'ab.c'
cmd = 'cflow -l --omit-symbol-names -o apt.txt ab.c'   #cflow execution
os.system(cmd)

G = nx.DiGraph()
fm = nx.DiGraph()

L=[]
level_list=[]
L_temp=[]
L_new=[]           
feature_list=[]   #contains the features
f_xor=[]


bodies=[]
st=[]



#class for pycparser tool execution to get the XOR relationship

class FuncVisitor(c_ast.NodeVisitor):
    def __init__(self, funcname):
     self.funcname = funcname

    def visit_FuncDef(self, node):
        if node.decl.name == self.funcname:
            v=IfVisitor(bodies)
            v.visit(node)
       
class IfVisitor(c_ast.NodeVisitor):
 def __init__(self, bodies):
    self.bodies = bodies
    self.generator = c_generator.CGenerator()
 def visit_If(self, node):
    self.bodies.append(self.generator.visit(node))

def show_funcs(filename, funcname):
    ast = parse_file(filename, use_cpp=True,cpp_path='gcc', cpp_args=['-E', r'-Ipycparser/utils/fake_libc_include'])
    v = FuncVisitor(funcname)
    v.visit(ast)
    if len(bodies)==0 :
     st.append('none')
    for body in bodies:
       st.append(body)   
    bodies.clear()




#text file in which outout of cflow is stored
with open("apt.txt") as f:
    L = f.readlines()
L = [x.strip() for x in L] 



#finding the indentation levels from output file

for i in range(len(L)):
 s=L[i]
 k=int(re.search(r'\d+', s).group())
 level_list.append(k)


#editing the list
for i in range(0,len(L)):
 s = L[i]
 for i,x in enumerate(s):
    if (x.isalpha()):         
     pos = i                  
     break
 new_str = s[pos:]
 L_temp.append(new_str)


for i in L_temp:
 if '(recursive: see' in i:
  #L_new.append(i[:i.index('>')+1]+" (R):")  #ignore the recursive functions
  level_list.pop(L_temp.index(i))
 else:
  L_new.append(i)

#print(*L_new,sep="\n")
#list edited and new list is L_new



lt=len(L_new)


#creating the call graph of the source code

for i in range(lt):
 G.add_node(i,value=L_new[i])

#print(*G.node.data(),sep="\n")

for i in range(0,lt-2):
 if(level_list[i]<level_list[i+1]):
  G.add_edge(i,i+1)
 elif(level_list[i]>=level_list[i+1]):
  for j in range(i,-1,-1):
   if(level_list[j]==level_list[i+1]-1):
    G.add_edge(j,i+1)
    break

for j in range(lt-2,-1,-1):
 if(level_list[j]==(level_list[lt-1]-1)):
  G.add_edge(j,lt-1)
  break

#print(*G.edges,sep="\n")




#creating feature_list

print("\nFeature list:\n")

for l in set(L_new):
 if(L_new.count(l)>1):
  feature_list.append(l)
 #if "(R)" in l: #recursive function added
  #feature_list.append(l)


fl_temp=[]
fl_temp=feature_list 
print(*feature_list,sep="\n")

for i in feature_list:
 f_xor.append(i[:i.index('(')])


#finding child subfetaures if present

ch = [[] for x in range(len(feature_list))]
ch_temp = [[] for x in range(len(feature_list))]

for i in range(len(feature_list)):
 nd = [x for x,y in G.nodes(data=True) if y['value']==feature_list[i]]
 for j in range(len(nd)):
   for k in G.successors(nd[j]):
    ch[i].append(G.nodes[k]['value'])

ch_temp=list(ch)

for i in range(len(ch)) :  
  ch[i]=list(set(ch[i]))


for i in range(len(ch)):
 if set(ch[i]) & set(feature_list):
  ch[i]=list(set(ch[i]).intersection(feature_list))
 else:
  ch[i]=[]


#print(*ch_temp,sep="\n")

#child sub-features found if present




#finding parents of the features

pr = [[] for x in range(len(feature_list))] 
pr_temp = [[] for x in range(len(feature_list))]

for i in range(len(feature_list)):
 nd = [x for x,y in G.nodes(data=True) if y['value']==feature_list[i]]
 for j in range(len(nd)):
   for k in G.predecessors(nd[j]):
    pr[i].append(G.nodes[k]['value'])


for i in range(len(pr)) :  
  pr[i]=list(set(pr[i]))

pr_temp=list(pr)

for i in range(len(pr)):
 if set(pr[i]) & set(feature_list):
  k=list(set(pr[i]).intersection(feature_list))
  if(len(k)==len(pr[i])):
   pr[i]=k
  else:
   pr[i]=k
   pr[i].append("variable_func")
 else:
  pr[i]=["variable_func"]
 
#print(*pr,sep="\n")

#parents found



#find siblings features if present

sibl = [[] for x in range(len(feature_list))] 
sibl_temp = [[] for x in range(len(feature_list))] 

for i in range(len(feature_list)):
 nd = [x for x,y in G.nodes(data=True) if y['value']==feature_list[i]]
 for j in range(len(nd)):
   for k in G.predecessors(nd[j]):
    for l in G.successors(k):
     if(G.nodes[l]['value']!=feature_list[i]):
      sibl[i].append(G.nodes[l]['value'])

sibl_temp=list(sibl)

for i in range(len(sibl)) :  
  sibl[i]=list(set(sibl[i]))


for i in range(len(sibl)):
 if set(sibl[i]) & set(feature_list):
  sibl[i]=list(set(sibl[i]).intersection(feature_list))
 else:
  sibl[i]=[]


#print(*sibl,sep="\n")

#siblings found


#creating feature model graph

fm.add_node('source',value='source',wg='na')


for i in range(len(feature_list)):
 s="variable_func"+str(i)
 if 'variable_func' in pr[i]:
  fm.add_node(s,value=s,wg=feature_list[i])
  fm.add_node(feature_list[i],value=feature_list[i],wg='na')
 else:
  fm.add_node(feature_list[i],value=feature_list[i],wg='na')


#print(*fm.node.data(),sep="\n")


nd = [x for x,y in fm.nodes(data=True) if y['wg']!='na']
for i in nd:
 fm.add_edge('source',i)

for i in range(len(feature_list)):
 if len(pr[i])==1 and pr[i]=='variable_func':
   nd = [x for x,y in fm.nodes(data=True) if y['wg']==feature_list[i]]
   fm.add_edge(*nd,feature_list[i])
 elif 'variable_func' in pr[i]:
  for j in pr[i]:
   if j!= 'variable_func':
    fm.add_edge(j,feature_list[i])
  nd = [x for x,y in fm.nodes(data=True) if y['wg']==feature_list[i]]
  fm.add_edge(*nd,feature_list[i])
 else:
  for j in pr[i]:
   fm.add_edge(j,feature_list[i])
 

#print(*fm.edges,sep="\n")

#check siblings relation

def check_sib(i,j):
 ti=np.setdiff1d(pr_temp[i],feature_list)
 tj=np.setdiff1d(pr_temp[j],feature_list)
 tk=list(set(ti).intersection(tj))
 if len(tk) > 0 :
  if len(tk)==len(ti) and len(tk)==len(tj) :
    return 1
  elif len(tk)<len(ti) and len(tk)==len(tj) :
    return 2
  elif len(tk)==len(ti) and len(tk)<len(tj):
    return 3
  else:
    return 4
 else:
  return 0
 

#adding nodes and edges if variable parents are present

for i in range(len(feature_list)):
 for j in range(i+1,len(feature_list)):
  if feature_list[j] in sibl[i]:
   k=check_sib(i,j)
   if k==1:
     nd = [x for x,y in fm.nodes(data=True) if feature_list[j] in y['wg'] or feature_list[i] in y['wg'] or s in y['wg']] 
     if len(nd)>1 :
      fm.nodes[nd[0]]['wg']=fm.nodes[nd[0]]['wg']+fm.nodes[nd[1]]['wg']
      fm=nx.contracted_nodes(fm, nd[0], nd[1])
      s=s+feature_list[i]+feature_list[j]
   if k==2:
    nd = [x for x,y in fm.nodes(data=True) if feature_list[j] in y['wg'] or s in y['wg']] 
    fm.add_edge(nd[0],feature_list[i])
   if k==3:
    nd = [x for x,y in fm.nodes(data=True) if feature_list[i] in y['wg'] or s in y['wg']]
    fm.add_edge(nd[0],feature_list[j])
   if k==4:
     fm.add_node("variable_func",value="variable_func",wg=s+feature_list[i]+feature_list[j])
     fm.add_edge("source","variable_func")
     fm.add_edge("variable_func",feature_list[i])
     fm.add_edge("variable_func",feature_list[j])
   

#checking xor relationship present or not

xl = [[] for x in range(len(f_xor))]  #contains the features which have xor relationship
for i in f_xor:
  show_funcs(filename, i)  #find the xor relation using AST generated by pycparser tool. Pycpasrer works for standard c libaries and headers. Look into documentation.
k=0
for i in st:
  if st!='none':
   for a in f_xor:
     if a in i:
       xl[k].append(a)
  else:
    xl[k].append('none')
  k=k+1


for i in range(len(xl)):
  if len(xl[i])<2:
    xl[i].clear

#print(*xl,sep="\n")


#find the relationships between feature and subfeatures

def find_rel(par,chi):
 chit=chi[:chi.index('(')]
 if 'variable_func' not in par:
  ind=feature_list.index(par)
  if chit in xl[ind]:
   return "XOR"
  elif ' (R):' in par and ' (R):' in chi :
   return "MANDATORY"
  elif L_new.count(par)==ch_temp[ind].count(chi):
   return "MANDATORY"
 elif 'variable_func' in par :
  return "OR"

 
for i in fm.edges.data():
 if 'variable_func' in i[1] and 'source' in i[0]:
  pass
 else:
   k=find_rel(i[0],i[1])
   fm.edges[i[0],i[1]]['rel']=k

for i in range(len(feature_list)):   #for finding optional relationship
 for j in range(i+1,len(feature_list)):
  if feature_list[j] in sibl[i] and feature_list[j] not in ch[i] and L_new.count(feature_list[i])!= sibl_temp[i].count(feature_list[j]) :
   if fm.has_edge(feature_list[i],feature_list[j]) or fm.has_edge(feature_list[j],feature_list[i]) :
    pass
   else:
    if L_new.count(feature_list[i])> L_new.count(feature_list[j]):
     fm.add_edge(feature_list[i],feature_list[j],rel='OPTIONAL')
    else:
     fm.add_edge(feature_list[j],feature_list[i],rel='OPTIONAL')

#print(*fm.edges.data(),sep="\n")

#display of original call graph

lbls={}
for i in G:
    lbls[i]=G.nodes[i]['value']
pos=nx.circular_layout(G)

nx.draw_circular(G,node_size=2000,node_color='pink',node_shape='o',width=2.0,with_labels=False)
nx.draw_networkx_labels(G,pos,lbls,font_size=10)
plt.axis('off')
plt.show() 


#display of feature model graph

labels={}
for i in fm: 
    labels[i]=fm.nodes[i]['value']
pos=nx.circular_layout(fm)


nx.draw_circular(fm,node_size=2000,node_color='pink',node_shape='o',width=2.5,with_labels=False)
nx.draw_networkx_labels(fm,pos,labels,font_size=12)
nx.draw_networkx_edge_labels(fm, pos, edge_labels=None, label_pos=0.5, font_size=8, font_color='r', rotate=True)
plt.axis('off')
plt.show() 














