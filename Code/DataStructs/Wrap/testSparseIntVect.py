# $Id$
#
# Copyright (C) 2007,2008 Greg Landrum
#
#  @@ All Rights Reserved @@
#
from rdkit import RDConfig
import os,sys,cPickle
import unittest
from rdkit import DataStructs as ds

def feq(v1,v2,tol=1e-4):
  return abs(v1-v2)<tol
class TestCase(unittest.TestCase):
  def setUp(self) :
    pass

  def test1Int(self):
    """

    """
    v1 = ds.IntSparseIntVect(5)
    self.failUnlessRaises(IndexError,lambda:v1[5])
    v1[0]=1
    v1[2]=2
    v1[3]=3
    self.failUnless(v1==v1)
    self.failUnless(v1.GetLength()==5)

    v2= ds.IntSparseIntVect(5)
    self.failUnless(v1!=v2)
    v2|=v1
    self.failUnless(v2==v1)

    v3=v2|v1
    self.failUnless(v3==v1)

    onVs = v1.GetNonzeroElements()
    self.failUnless(onVs=={0:1,2:2,3:3})


  def test2Long(self):
    """

    """
    l=1L<<42
    v1 = ds.LongSparseIntVect(l)
    self.failUnlessRaises(IndexError,lambda:v1[l])
    v1[0]=1
    v1[2]=2
    v1[1L<<35]=3
    self.failUnless(v1==v1)
    self.failUnless(v1.GetLength()==l)

    v2= ds.LongSparseIntVect(l)
    self.failUnless(v1!=v2)
    v2|=v1
    self.failUnless(v2==v1)

    v3=v2|v1
    self.failUnless(v3==v1)

    onVs = v1.GetNonzeroElements()
    self.failUnless(onVs=={0L:1,2L:2,1L<<35:3})

  def test3Pickle1(self):
    """

    """
    l=1L<<42
    v1 = ds.LongSparseIntVect(l)
    self.failUnlessRaises(IndexError,lambda:v1[l+1])
    v1[0]=1
    v1[2]=2
    v1[1L<<35]=3
    self.failUnless(v1==v1)

    v2=  cPickle.loads(cPickle.dumps(v1))
    self.failUnless(v2==v1)
    
    v3=  ds.LongSparseIntVect(v2.ToBinary())
    self.failUnless(v2==v3)
    self.failUnless(v1==v3)

    #cPickle.dump(v1,file('lsiv.pkl','wb+'))
    v3 = cPickle.load(file(os.path.join(RDConfig.RDBaseDir,
                                        'Code/DataStructs/Wrap/testData/lsiv.pkl'),'rb'))
    self.failUnless(v3==v1)
    
  def test3Pickle2(self):
    """

    """
    l=1L<<21
    v1 = ds.IntSparseIntVect(l)
    self.failUnlessRaises(IndexError,lambda:v1[l+1])
    v1[0]=1
    v1[2]=2
    v1[1<<12]=3
    self.failUnless(v1==v1)

    v2=  cPickle.loads(cPickle.dumps(v1))
    self.failUnless(v2==v1)
    
    v3=  ds.IntSparseIntVect(v2.ToBinary())
    self.failUnless(v2==v3)
    self.failUnless(v1==v3)

    #cPickle.dump(v1,file('isiv.pkl','wb+'))
    v3 = cPickle.load(file(os.path.join(RDConfig.RDBaseDir,
                                        'Code/DataStructs/Wrap/testData/isiv.pkl'),'rb'))
    self.failUnless(v3==v1)

  def test4Update(self):
    """

    """
    v1 = ds.IntSparseIntVect(5)
    self.failUnlessRaises(IndexError,lambda:v1[6])
    v1[0]=1
    v1[2]=2
    v1[3]=3
    self.failUnless(v1==v1)

    v2 = ds.IntSparseIntVect(5)
    v2.UpdateFromSequence((0,2,3,3,2,3))
    self.failUnless(v1==v2)
    
  def test5Dice(self):
    """

    """
    v1 = ds.IntSparseIntVect(5)
    v1[4]=4;
    v1[0]=2;
    v1[3]=1;
    self.failUnless(feq(ds.DiceSimilarity(v1,v1),1.0))

    v1 = ds.IntSparseIntVect(5)
    v1[0]=2;
    v1[2]=1;
    v1[3]=4;
    v1[4]=6;
    v2 = ds.IntSparseIntVect(5)
    v2[1]=2;
    v2[2]=3;
    v2[3]=4;
    v2[4]=4;
    self.failUnless(feq(ds.DiceSimilarity(v1,v2),18.0/26.))
    self.failUnless(feq(ds.DiceSimilarity(v2,v1),18.0/26.))

  def test6BulkDice(self):
    """

    """
    sz=10
    nToSet=5
    nVs=6
    import random
    vs = []
    for i in range(nVs):
      v = ds.IntSparseIntVect(sz)
      for j in range(nToSet):
        v[random.randint(0,sz-1)]=random.randint(1,10)
      vs.append(v)

    baseDs = [ds.DiceSimilarity(vs[0],vs[x]) for x in range(1,nVs)]
    bulkDs = ds.BulkDiceSimilarity(vs[0],vs[1:])
    for i in range(len(baseDs)):
      self.failUnless(feq(baseDs[i],bulkDs[i]))

  def test6BulkTversky(self):
    """

    """
    sz=10
    nToSet=5
    nVs=6
    import random
    vs = []
    for i in range(nVs):
      v = ds.IntSparseIntVect(sz)
      for j in range(nToSet):
        v[random.randint(0,sz-1)]=random.randint(1,10)
      vs.append(v)

    baseDs = [ds.TverskySimilarity(vs[0],vs[x],.5,.5) for x in range(1,nVs)]
    bulkDs = ds.BulkTverskySimilarity(vs[0],vs[1:],0.5,0.5)
    diceDs = [ds.DiceSimilarity(vs[0],vs[x]) for x in range(1,nVs)]
    for i in range(len(baseDs)):
      self.failUnless(feq(baseDs[i],bulkDs[i]))
      self.failUnless(feq(baseDs[i],diceDs[i]))
    
    bulkDs = ds.BulkTverskySimilarity(vs[0],vs[1:],1.0,1.0)
    taniDs = [ds.TanimotoSimilarity(vs[0],vs[x]) for x in range(1,nVs)]
    for i in range(len(bulkDs)):
      self.failUnless(feq(bulkDs[i],taniDs[i]))
    taniDs = ds.BulkTanimotoSimilarity(vs[0],vs[1:])
    for i in range(len(bulkDs)):
      self.failUnless(feq(bulkDs[i],taniDs[i]))
    
    
if __name__ == '__main__':
    unittest.main()
