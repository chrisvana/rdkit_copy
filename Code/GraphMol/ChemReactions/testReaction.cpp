// $Id$
//
//  Copyright (c) 2007, Novartis Institutes for BioMedical Research Inc.
//  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met: 
//
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following 
//       disclaimer in the documentation and/or other materials provided 
//       with the distribution.
//     * Neither the name of Novartis Institutes for BioMedical Research Inc. 
//       nor the names of its contributors may be used to endorse or promote 
//       products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#include <RDGeneral/RDLog.h>
#include <RDGeneral/utils.h>
#include <GraphMol/RDKitBase.h>
#include <string>
#include <iostream>
#include <Geometry/point.h>
#include <GraphMol/SmilesParse/SmilesParse.h>
#include <GraphMol/SmilesParse/SmilesWrite.h>
#include <GraphMol/ChemReactions/Reaction.h>
#include <GraphMol/ChemReactions/ReactionParser.h>
#include <GraphMol/ChemReactions/ReactionPickler.h>

using namespace RDKit;

void test1Basics(){
  ROMol *mol=0;
  ChemicalReaction rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing ChemicalReaction infrastructure" << std::endl;

  smi = "[C:1](=[O:2])O";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==1);
  
  smi = "[N:3][C:4]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==2);
  
  smi = "[C:1](=[O:2])[N:3][C:4]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addProductTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumProductTemplates()==1);

  smi = "C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  rxn.initReactantMatchers();
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  
  reacts.clear();
  smi = "CC(C(=O)O)C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==2);
  
  reacts.clear();
  smi = "CC(C(=O)O)C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "NCN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==4);

  
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test2SimpleReactions(){
  ROMol *mol=0;
  ChemicalReaction rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing simple reactions" << std::endl;

  smi = "[C:1](=[O:2])O";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==1);
  
  smi = "[N:3][C:4]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==2);
  
  smi = "[C:1](=[O:2])[N:3][C:4]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addProductTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumProductTemplates()==1);

  smi = "C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn.initReactantMatchers();
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);
  
  reacts.clear();
  smi = "CC(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
  TEST_ASSERT(prods[0][0]->getNumBonds()==4);
  
  reacts.clear();
  smi = "CC(C(=O)O)C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==2);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[1].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==9);
  TEST_ASSERT(prods[1][0]->getNumAtoms()==9);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
    
  reacts.clear();
  smi = "CC(C(=O)O)C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "NCN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[1].size()==1);
  TEST_ASSERT(prods[2].size()==1);
  TEST_ASSERT(prods[3].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==10);
  TEST_ASSERT(prods[1][0]->getNumAtoms()==10);
  TEST_ASSERT(prods[2][0]->getNumAtoms()==10);
  TEST_ASSERT(prods[3][0]->getNumAtoms()==10);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));
  

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
  
}


void test3RingFormation(){
  ROMol *mol=0;
  ChemicalReaction rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing ring formation reactions" << std::endl;

  smi = "[C:1]=[C:2]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==1);
  
  smi = "[C:3]=[C:4][C:5]=[C:6]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==2);
  
  smi = "[C:1]1[C:2][C:3][C:4]=[C:5][C:6]1";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addProductTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumProductTemplates()==1);

  smi = "C=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "C=CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn.initReactantMatchers();
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==6);

  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));
    
  reacts.clear();
  smi = "CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "C=CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==7);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));

  reacts.clear();
  smi = "CC=C[Cl]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "[F]C=CC=C[Br]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==10);
  for(unsigned int i=0;i<prods.size();i++){
    unsigned int nDifferent=0;
    for(unsigned int j=0;j<prods.size();j++){
      if(MolToSmiles(*prods[i][0])!=MolToSmiles(*prods[j][0])) nDifferent += 1;
    }
    TEST_ASSERT(nDifferent==2);
  }

  reacts.clear();
  smi = "C1C=CCCC1";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "C=CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==10);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test4MultipleProducts(){
  ROMol *mol=0;
  ChemicalReaction rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing reactions forming multiple products" << std::endl;

  // yes, I know this is bogus... it's a test!
  smi = "[N:1][C:2][C:3](=[O:4])[O:5]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==1);
  
  smi = "[N:6][C:7][C:8](=[O:9])[O:10]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==2);
  
  smi = "[N:1]1[C:2][C:3](=[O:4])[N:6][C:7][C:8]1=[O:9]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addProductTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumProductTemplates()==1);

  smi = "[O:5][O:10]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addProductTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumProductTemplates()==2);

  smi = "OC(=O)CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "OC(=O)CN";    
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn.initReactantMatchers();
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==2);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
  TEST_ASSERT(prods[0][1]->getNumAtoms()==2);
  smi=MolToSmiles(*prods[0][0]);
  std::cerr<<"smi: "<<smi<<std::endl;
  TEST_ASSERT(smi=="O=C1CNC(=O)CN1");
  TEST_ASSERT(MolToSmiles(*prods[0][1])=="OO");

  reacts.clear();
  smi = "COC(=O)CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "COC(=O)CN";    
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));


  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==2);
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][0].get())));
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][1].get())));
  std::cerr<<"1: "<<MolToSmiles(*prods[0][0])<<std::endl;
  std::cerr<<"2: "<<MolToSmiles(*prods[0][1])<<std::endl;
  TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
  TEST_ASSERT(prods[0][1]->getNumAtoms()==4);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  TEST_ASSERT(MolToSmiles(*prods[0][1])=="COOC");


  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test5Salts(){
  ROMol *mol=0;
  ChemicalReaction rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing salt handling" << std::endl;

  smi = "[C:1](=[O:2])O";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==1);
  
  smi = "[N:3][C:4]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addReactantTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumReactantTemplates()==2);
  
  smi = "[C:1](=[O:2])[N:3][C:4]";
  mol = SmartsToMol(smi);
  TEST_ASSERT(mol);
  rxn.addProductTemplate(ROMOL_SPTR(mol));
  TEST_ASSERT(rxn.getNumProductTemplates()==1);

  smi = "C(=O)O.[ClH]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN.C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn.initReactantMatchers();
  prods = rxn.runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test6DaylightParser(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing Daylight parser" << std::endl;

  smi = "[C:1](=[O:2])O.[N:3][C:4]>>[C:1](=[O:2])[N:3][C:4]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  smi = "C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);
  
  delete rxn;
  reacts.clear();
  smi = "[N:1][C:2][C:3](=[O:4])[O:5].[N:6][C:7][C:8](=[O:9])[O:10]>>[N:1]1[C:2][C:3](=[O:4])[N:6][C:7][C:8]1=[O:9].[O:5][O:10]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==2);

  smi = "OC(=O)CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "OC(=O)CN";    
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==2);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
  TEST_ASSERT(prods[0][1]->getNumAtoms()==2);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  TEST_ASSERT(MolToSmiles(*prods[0][1])=="OO");


  delete rxn;
  reacts.clear();
  smi = "[N:1][C:2][C:3](=[O:4])[O:5].[N:6][C:7][C:8](=[O:9])[O:10].[N:1]1[C:2][C:3](=[O:4])[N:6][C:7][C:8]1=[O:9].[O:5][O:10]";
  try{
    rxn = RxnSmartsToChemicalReaction(smi); 
  } catch (ChemicalReactionParserException &) {
  }
  
  smi = "[N:1][C:2][C:3](=[O:4])[O:5].[N:6][C:7][C:8](=[O:9])[O:10]>>[N:1]1[C:2][C:3](=[O:4])[N:6][C:7][C:8]1=[O:9]>>[O:5][O:10]";
  try{
    rxn = RxnSmartsToChemicalReaction(smi); 
  } catch (ChemicalReactionParserException &) {
  }

  smi = "[Q:1][C:2][C:3](=[O:4])[O:5].[N:6][C:7][C:8](=[O:9])[O:10]>>[N:1]1[C:2][C:3](=[O:4])[N:6][C:7][C:8]1=[O:9].[O:5][O:10]";
  try{
    rxn = RxnSmartsToChemicalReaction(smi); 
  } catch (ChemicalReactionParserException &) {
  }
  

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test7MDLParser(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing MDL parser" << std::endl;

  std::string rdbase = getenv("RDBASE");
  std::string fName;
  
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/AmideBond.rxn";

  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  smi = "C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);


  delete rxn;
  reacts.clear();
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/cyclization1.rxn";
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);


  smi = "OC(=O)CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "OC(=O)CN";    
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
  std::cerr<<MolToSmiles(*prods[0][0])<<std::endl;
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  
  delete rxn;
  reacts.clear();
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/cyclization1.rxn";
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);


  smi = "OC(=O)CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "OC(=O)CN";    
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  
  delete rxn;
  reacts.clear();
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/cyclization2.rxn";
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  smi = "CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "C=CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==7);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));
  
  reacts.clear();
  smi = "CC=C[Cl]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "[F]C=CC=C[Br]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==10);
  for(unsigned int i=0;i<prods.size();i++){
    unsigned int nDifferent=0;
    for(unsigned int j=0;j<prods.size();j++){
      if(MolToSmiles(*prods[i][0])!=MolToSmiles(*prods[j][0])) nDifferent += 1;
    }
    TEST_ASSERT(nDifferent==2);
  }

  reacts.clear();
  smi = "C1C=CCCC1";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "C=CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==10);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));
  
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test8Validation(){
  ChemicalReaction *rxn;
  unsigned int nWarn,nError;

  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing Reaction Validation." << std::endl;

  smi = "[C:1](=[O:2])O.[N:3][C:4]>>[C:1](=[O:2])[N:3][C:4]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->validate(nWarn,nError,true));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);
  
  smi = "[C:1](=[O:2])[O:5].[N:3][C:4]>>[C:1](=[O:2])[N:3][C:4]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->validate(nWarn,nError,true));
  TEST_ASSERT(nWarn==1);
  TEST_ASSERT(nError==0);
  
  smi = "[C:1](=[O:2])O.[N:1][C:4]>>[C:1](=[O:2])[N:3][C:4]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(!rxn->validate(nWarn,nError,true));
  TEST_ASSERT(nWarn==1);
  TEST_ASSERT(nError==1);
  
  smi = "[C:1](=[O:2])O.[N:3][C:4]>>[C:1](=[O:2])[N:3][C:5]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->validate(nWarn,nError,true));
  TEST_ASSERT(nWarn==2);
  TEST_ASSERT(nError==0);

  smi = "[C:1](=[O:2])O.[N:3][C:4]>>[C:1](=[O:2])[N:3][C:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(!rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==1);
  TEST_ASSERT(nError==1);

  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test9ProductQueries(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing handling of query atoms in the products" << std::endl;

  smi = "[C:1](=[O:2])O.[N:3]>>[C:1](=[O:2])[*:3]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);

  smi = "C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);
  
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(2)->getAtomicNum()==7);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="CNC=O");
  
  delete rxn;
  smi = "[C:1](=[O:2])O.[N:3]>>[C:1](=[*:2])[*:3]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);
  
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(2)->getAtomicNum()==7);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="CNC=O");

  delete rxn;
  smi = "[C:1](=[O:2])O.[N:3]>>[*:1](=[*:2])[*:3]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);
  
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(2)->getAtomicNum()==7);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="CNC=O");

  delete rxn;
  smi = "[*:1]1:[*:2]:[*:3]:[*:4]:[*:5]:[*:6]:1>>[*:1]1:[*:2]:[*:3]:[*:4]:[*:5]:[*:6]:1C";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);

  reacts.clear();
  smi = "c1ccccc1";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==12);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==7);
  
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getIsAromatic());
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(1)->getIsAromatic());
  TEST_ASSERT(prods[0][0]->getBondBetweenAtoms(0,1)->getIsAromatic());
  
  delete rxn;


  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test10ChiralityDaylight(){
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing Chirality handling" << std::endl;


  { // default behavior, make no changes w.r.t. stereochem
    std::string smi = "[F:1][C:2]([Cl:3])([Br:4])[I:5]>>[*:1][C:2]([*:3])([*:4])[*:5]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    
    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "F[C@](Cl)(Br)I";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@](Cl)(Br)I");
  
    reacts.clear();
    smi = "F[C@@](Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@@](Cl)(Br)I");

    reacts.clear();
    smi = "FC(Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="FC(Cl)(Br)I");

    delete rxn;
  }

  { // a reaction that retains stereochem
    std::string smi = "[F:1][C@:2]([Cl:3])([Br:4])[I:5]>>[*:1][C@:2]([*:3])([*:4])[*:5]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    
    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "F[C@](Cl)(Br)I";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@](Cl)(Br)I");
  
    reacts.clear();
    smi = "F[C@@](Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@@](Cl)(Br)I");

    reacts.clear();
    smi = "FC(Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="FC(Cl)(Br)I");

    delete rxn;
  }
  { // a reaction that inverts stereochem
    std::string smi = "[F:1][C@:2]([Cl:3])([Br:4])[I:5]>>[*:1][C@@:2]([*:3])([*:4])[*:5]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    
    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "F[C@](Cl)(Br)I";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@@](Cl)(Br)I");
  
    reacts.clear();
    smi = "F[C@@](Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@](Cl)(Br)I");

    reacts.clear();
    smi = "FC(Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="FC(Cl)(Br)I");

    delete rxn;
  }

  { // a reaction that induces/sets stereochem
    std::string smi = "[F:1][C:2]([Cl:3])([Br:4])[I:5]>>[*:1][C@@:2]([*:3])([*:4])[*:5]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    
    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "F[C@](Cl)(Br)I";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@@](Cl)(Br)I");
  
    reacts.clear();
    smi = "F[C@@](Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@@](Cl)(Br)I");

    reacts.clear();
    smi = "FC(Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@@](Cl)(Br)I");

    delete rxn;
  }
  { // a reaction that induces/sets stereochem
    std::string smi = "[F:1][C:2]([Cl:3])([Br:4])[I:5]>>[*:1][C@:2]([*:3])([*:4])[*:5]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    
    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "F[C@](Cl)(Br)I";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@](Cl)(Br)I");
  
    reacts.clear();
    smi = "F[C@@](Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@](Cl)(Br)I");

    reacts.clear();
    smi = "FC(Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="F[C@](Cl)(Br)I");

    delete rxn;
  }
  { // a reaction that removes stereochem
    std::string smi = "[F:1][C@:2]([Cl:3])([Br:4])[I:5]>>[*:1][C:2]([*:3])([*:4])[*:5]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    
    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "F[C@](Cl)(Br)I";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="FC(Cl)(Br)I");
  
    reacts.clear();
    smi = "F[C@@](Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="FC(Cl)(Br)I");

    reacts.clear();
    smi = "FC(Cl)(Br)I";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumBonds()==4);
    BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
    TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="FC(Cl)(Br)I");

    delete rxn;
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test11ChiralityRxn(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing Chirality handling (rxn)" << std::endl;

  std::string rdbase = getenv("RDBASE");
  std::string fName;
  
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/SN2_FlagProd.rxn";

  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==2);

  reacts.clear();
  smi = "F[C@@](Cl)(Br)I";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  smi = "[OH-]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==2);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
  TEST_ASSERT(prods[0][0]->getNumBonds()==4);
  TEST_ASSERT(prods[0][1]->getNumAtoms()==1);
  TEST_ASSERT(prods[0][1]->getNumBonds()==0);
  TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="O[C@](F)(Cl)I");
  TEST_ASSERT(MolToSmiles(*prods[0][1],true)=="[Br-]");

  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/SN2_FlagProd.retain.rxn";

  delete rxn;
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==2);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==2);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
  TEST_ASSERT(prods[0][0]->getNumBonds()==4);
  TEST_ASSERT(prods[0][1]->getNumAtoms()==1);
  TEST_ASSERT(prods[0][1]->getNumBonds()==0);
  TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="O[C@@](F)(Cl)I");
  TEST_ASSERT(MolToSmiles(*prods[0][1],true)=="[Br-]");

  // this has the chirality flag in the reactants, which is ignored, so the chirality is preserved:
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/SN2_FlagReact.rxn";
  delete rxn;
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==2);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==2);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
  TEST_ASSERT(prods[0][0]->getNumBonds()==4);
  TEST_ASSERT(prods[0][1]->getNumAtoms()==1);
  TEST_ASSERT(prods[0][1]->getNumBonds()==0);
  TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="O[C@@](F)(Cl)I"); 
  TEST_ASSERT(MolToSmiles(*prods[0][1],true)=="[Br-]");
  
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test12DoubleBondStereochem(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi,stereo;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing handling of double bond stereochemistry" << std::endl;

  smi = "[C:1](=[O:2])-[O;H0]>>[C:1](=[O:2])[X]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  reacts.clear();
  smi = "COC(=O)/C=C/Cl";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  MolOps::assignStereochemistry(*mol);
    
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==6);
  TEST_ASSERT(prods[0][0]->getNumBonds()==5);
  prods[0][0]->updatePropertyCache();
  BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
  MolOps::assignStereochemistry(*(prods[0][0]));
  TEST_ASSERT(mol->getBondWithIdx(4)->getStereo()==Bond::STEREOE);
  TEST_ASSERT(prods[0][0]->getBondWithIdx(3)->getStereo()==Bond::STEREOE);
    
  reacts.clear();

  //FIX: note that the handling of this situation, where we match double bonds that
  // have stereochem indicated, is currently not completely correct since the
  // stereochem querying stuff doesn't match C/C=C\Cl when C\C=C/Cl is provided as 
  // a query.  
  delete rxn;
  smi = "[Cl:3]\\[C:1]=[C:2]/[C:4]>>[Cl:3]\\[C:1]=[C:2]\\[C:4]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  reacts.clear();
  smi = "Cl\\C=C/C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  MolOps::assignStereochemistry(*mol);
    
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);
  prods[0][0]->updatePropertyCache();
  BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
  MolOps::assignStereochemistry(*(prods[0][0]));
  TEST_ASSERT(mol->getBondWithIdx(1)->getStereo()==Bond::STEREOZ);
  TEST_ASSERT(prods[0][0]->getBondWithIdx(1)->getStereo()==Bond::STEREOE);
    
  reacts.clear();
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test13Issue1748846(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi,stereo;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing sf.net Issue 1748846: bad bond orders in reaction products" << std::endl;

  smi = "c1ccccc1[C:1].[*:2][At]>>c1ccccc1[C:1][*:2]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  reacts.clear();
  smi = "c1ccccc1C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "[At]OC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()>0);
  BOOST_LOG(rdInfoLog)<<prods[0].size()<<std::endl;
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==9);
  BOOST_LOG(rdInfoLog)<<MolToSmiles(*prods[0][0],true)<<std::endl;
  TEST_ASSERT(prods[0][0]->getBondBetweenAtoms(0,1)->getBondType()==Bond::AROMATIC);
  TEST_ASSERT(prods[0][0]->getBondBetweenAtoms(1,2)->getBondType()==Bond::AROMATIC);
  smi=MolToSmiles(*prods[0][0],true);
  TEST_ASSERT(smi=="COCc1ccccc1");
  
  delete rxn;
  smi = "[c:3][C:1].[*:2][At]>>[c:3][C:1][*:2]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  reacts.clear();
  smi = "c1ccccc1C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "[At]OC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()>0);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==9);
  smi=MolToSmiles(*prods[0][0],true);
  TEST_ASSERT(smi=="COCc1ccccc1");
    
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test14Issue1804420(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi,stereo;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing sf.net Issue 1804420: bad handling of query atoms in products." << std::endl;

  // NOTE that this bug was actually in the smarts parser, so this is really
  // just another reaction test... still, more tests are better
  
  smi = "[N;D3;R:1]-!@[*:2]>>[At][N:1].[*:2][At]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==2);

  TEST_ASSERT((*rxn->beginReactantTemplates())->getAtomWithIdx(0)->hasProp("molAtomMapNumber"));
  
  reacts.clear();
  smi = "C1CCN1CCC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==2);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
  smi=MolToSmiles(*prods[0][0],true);
  TEST_ASSERT(smi=="[At]N1CCC1");
  TEST_ASSERT(prods[0][1]->getNumAtoms()==4);
  smi=MolToSmiles(*prods[0][1],true);
  TEST_ASSERT(smi=="CCC[At]");

  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test15Issue1882749(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  unsigned int nWarn,nError;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing sf.net Issue 1882749: property handling in products." << std::endl;

  smi = "[N:1]-!@[*]>>[N;+1,+0:1][#0]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==1);
  TEST_ASSERT(nError==0);

  delete rxn;
  smi = "[N:1]-!@[*]>>[N;-1:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);

  reacts.clear();
  smi = "C1CCN1CCC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getFormalCharge()==-1);

  delete rxn;
  smi = "[N;D3:1]-!@[*]>>[N;H1:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getNumExplicitHs()==1);

  delete rxn;
  smi = "[N;D3:1]-!@[*]>>[15N:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getAtomicNum()==7);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getIsotope()==15);
  std::cerr<<" mass: "<<prods[0][0]->getAtomWithIdx(0)->getMass()<<std::endl;
  TEST_ASSERT(feq(prods[0][0]->getAtomWithIdx(0)->getMass(),15.0001));

  delete rxn;
  smi = "[N;D3:1]-!@[*]>>[15N;-1:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getFormalCharge()==-1);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getIsotope()==15);
  TEST_ASSERT(feq(prods[0][0]->getAtomWithIdx(0)->getMass(),15.0001));

  reacts.clear();
  smi = "CS(=O)C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  delete rxn;
  smi = "[S:1]=[O:2]>>[S;+2:1]-[O;-:2]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(0)->getFormalCharge()==+2);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(1)->getFormalCharge()==-1);

  reacts.clear();
  smi = "CO";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  delete rxn;
  smi = "[O:1]>>[O:1][13C]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==3);
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(1)->getIsotope()==13);
  TEST_ASSERT(feq(prods[0][0]->getAtomWithIdx(1)->getMass(),13.00335));
  
  reacts.clear();
  smi = "CO";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  delete rxn;
  smi = "[O:1]>>[O:1][3#0]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==3);
  
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][0].get())));
  TEST_ASSERT(prods[0][0]->getAtomWithIdx(1)->getIsotope()==3);
  TEST_ASSERT(feq(prods[0][0]->getAtomWithIdx(1)->getMass(),0.000));
  TEST_ASSERT(MolToSmiles(*prods[0][0],true)=="[3*]OC");

  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test16Exceptions(){
  ChemicalReaction *rxn;
  std::string rxnB;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing parser exception handling" << std::endl;

  
  rxnB="$RXN\n"
    "\n"
    "      ISIS     082120061354\n"
    "\n"
    "  2  1\n"
    "$MOL\n"
    "\n"
    "  -ISIS-  08210613542D\n"
    "\n"
    "  4  2  0  0  0  0  0  0  0  0999 V2000\n"
    "   -1.4340   -0.6042    0.0000 C   0  0  0  0  0  0  0  0  0  2  0  0\n"
    "   -0.8639   -0.9333    0.0000 O   0  0  0  0  0  0  0  0  0  0  0  0\n"
    "   -1.4340    0.0542    0.0000 O   0  0  0  0  0  0  0  0  0  1  0  0\n"
    "  1  2  1  0  0  0  0\n"
    "  1  3  2  0  0  0  0\n"
    "M  END\n"
    "$MOL\n"
    "\n"
    "  -ISIS-  08210613542D\n"
    "\n"
    "  1  0  0  0  0  0  0  0  0  0999 V2000\n"
    "    2.2125   -0.7833    0.0000 N   0  0  0  0  0  0  0  0  0  3  0  0\n"
    "M  END\n"
    "$MOL\n"
    "\n"
    "  -ISIS-  08210613542D\n"
    "\n"
    "  3  2  0  0  0  0  0  0  0  0999 V2000\n"
    "    9.5282   -0.8083    0.0000 N   0  0  0  0  0  0  0  0  0  3  0  0\n"
    "    8.9579   -0.4792    0.0000 C   0  0  0  0  0  0  0  0  0  2  0  0\n"
    "    8.9579    0.1792    0.0000 O   0  0  0  0  0  0  0  0  0  1  0  0\n"
    "  1  2  1  0  0  0  0\n"
    "  2  3  2  0  0  0  0\n"
    "M  END\n";

  rxn=(ChemicalReaction *)0x1;
  try {
    rxn = RxnBlockToChemicalReaction(rxnB);
  } catch (ChemicalReactionParserException &){
    rxn=(ChemicalReaction *)0x0;
  }
  TEST_ASSERT(!rxn);
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}



void test17Issue1920627(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  ROMOL_SPTR prod;
  std::string smi,cip;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing sf.net Issue 1920627: chirality flip in reactions." << std::endl;

  smi = "[C:1](=[O:2])>>[C:1](=[S:2])";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

#if 1
  reacts.clear();
  smi = "C[C@](Cl)(CO)CC(=O)NC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(1)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(1)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
  
  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==10);
  TEST_ASSERT(prod->getAtomWithIdx(4)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(4)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
  
  reacts.clear();
  smi = "C[C@H](CO)CC(=O)NC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(1)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(1)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="S");
  
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==9);
  TEST_ASSERT(prod->getAtomWithIdx(4)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(4)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="S");
  
  // make sure the above two tests work "backwards":
  reacts.clear();
  smi = "C[C@@](Cl)(CO)CC(=O)NC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(1)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(1)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="S");
  
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==10);
  TEST_ASSERT(prod->getAtomWithIdx(4)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(4)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="S");
  
  reacts.clear();
  smi = "C[C@@H](CO)CC(=O)NC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(1)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(1)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==9);
  TEST_ASSERT(prod->getAtomWithIdx(4)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(4)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");

  // do some "restructuring" and make sure things still work:
  reacts.clear();
  smi = "[C@@](C)(Cl)(CO)CC(=O)NC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(0)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(0)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="S");
  
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==10);
  TEST_ASSERT(prod->getAtomWithIdx(4)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(4)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="S");
  
  reacts.clear();
  smi = "[C@H](C)(CO)CC(=O)NC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(0)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(0)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
  
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==9);
  TEST_ASSERT(prod->getAtomWithIdx(4)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(4)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
#endif

  reacts.clear();
  smi = "C(=O)N[C@@H](CC)C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(3)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(3)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
  
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==7);
  TEST_ASSERT(prod->getAtomWithIdx(3)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(3)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");

  reacts.clear();
  smi = "C(=O)N[C@@H](CC)C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);
  TEST_ASSERT(mol->getAtomWithIdx(3)->hasProp("_CIPCode"));
  mol->getAtomWithIdx(3)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
  
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
  MolOps::assignStereochemistry(*prod);
  TEST_ASSERT(prod->getNumAtoms()==7);
  TEST_ASSERT(prod->getAtomWithIdx(3)->hasProp("_CIPCode"));
  prod->getAtomWithIdx(3)->getProp("_CIPCode",cip);
  TEST_ASSERT(cip=="R");
  
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test18PropertyTransfer(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  ROMOL_SPTR prod;
  std::string smi,cip;
  unsigned int nWarn,nError;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing property transfer in reactions." << std::endl;


  // ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ -----
  // start with sf.net Issue 1934052: propagation of isotope information 
  smi = "[C:1]>>[C:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);

  reacts.clear();
  smi = "C";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==1);
  TEST_ASSERT(feq(prod->getAtomWithIdx(0)->getMass(),12,.1));

  reacts.clear();
  smi = "[13CH4]";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==1);
  TEST_ASSERT(feq(prod->getAtomWithIdx(0)->getMass(),13,.1));
  
  delete rxn;
  smi = "[12C:1]>>[13C:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);

  reacts.clear();
  smi = "[12CH4]";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==1);
  TEST_ASSERT(prod->getAtomWithIdx(0)->getIsotope()==13);
  TEST_ASSERT(feq(prod->getAtomWithIdx(0)->getMass(),13.003,.001));

  reacts.clear();
  smi = "[13CH4]";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==0);

  delete rxn;
  smi = "[13C:1]>>[12C:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);

  reacts.clear();
  smi = "[13CH4]";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==1);
  TEST_ASSERT(prod->getAtomWithIdx(0)->getIsotope()==12);
  TEST_ASSERT(feq(prod->getAtomWithIdx(0)->getMass(),12,.001));

  reacts.clear();
  smi = "C";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==0);

  delete rxn;
  smi = "[C:1]>>[12C:1]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);

  reacts.clear();
  smi = "C";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==1);
  TEST_ASSERT(prod->getAtomWithIdx(0)->getIsotope()==12);
  TEST_ASSERT(feq(prod->getAtomWithIdx(0)->getMass(),12,.001));

  reacts.clear();
  smi = "[13CH4]";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==1);
  TEST_ASSERT(prod->getAtomWithIdx(0)->getIsotope()==12);
  TEST_ASSERT(feq(prod->getAtomWithIdx(0)->getMass(),12,.001));

  delete rxn;
  smi = "[C:1](=[O:2])>>[C:1](=[S:2])";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);

  reacts.clear();
  smi = "C=O";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==2);
  TEST_ASSERT(feq(prod->getAtomWithIdx(0)->getMass(),12,.1));
  TEST_ASSERT(feq(prod->getAtomWithIdx(1)->getMass(),32,.1));
  
  // ------ ------ ------ ------ ------ ------ ------ ------ ------ ------ -----
  // now look at some other properties
  delete rxn;
  smi = "[c;H1:1][n:2]>>[c:1](O)[n:2]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);
  TEST_ASSERT(rxn->validate(nWarn,nError,false));
  TEST_ASSERT(nWarn==0);
  TEST_ASSERT(nError==0);

  reacts.clear();
  smi = "c1ccccn1";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==2);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==7);
  smi=MolToSmiles(*prod);
  std::cerr<<smi<<std::endl;
  TEST_ASSERT(smi=="Oc1ccccn1");

  reacts.clear();
  smi = "c1ccc[nH]1";
  mol = SmilesToMol(smi);
  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==2);
  TEST_ASSERT(prods[0].size()==1);
  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==6);
  smi=MolToSmiles(*prod);
  std::cerr<<smi<<std::endl;
  TEST_ASSERT(smi=="Oc1ccc[nH]1");
  
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}



void test19Issue2050085(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  ROMOL_SPTR prod;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing sf.net Issue 2050085: recap failing on chiral molecules." << std::endl;

  smi = "[N;!D1;+0](-!@[*:1])-!@[*:2]>>[*][*:1].[*:2][*]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==2);

  reacts.clear();
  smi = "C1CC1N[C@H](C)F";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  MolOps::assignStereochemistry(*mol);

  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==2);
  TEST_ASSERT(prods[0].size()==2);
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][0].get())));
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][1].get())));

  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==4);
  prod = prods[0][1];
  TEST_ASSERT(prod->getNumAtoms()==4);

  
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test20BondQueriesInProduct(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  ROMOL_SPTR prod;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing bond queries in the product." << std::endl;

  smi = "[O:1]~[C:2]>>[O:1]~[C:2]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  reacts.clear();
  smi = "OCC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);

  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][0].get())));

  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==3);
  TEST_ASSERT(prod->getBondBetweenAtoms(0,1)->getBondType()==Bond::SINGLE);

  reacts.clear();
  smi = "O=CC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);

  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][0].get())));

  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==3);
  TEST_ASSERT(prod->getBondBetweenAtoms(0,1)->getBondType()==Bond::DOUBLE);
  delete rxn;

  smi = "[O:1]~[C:2]>>[O:1][C:2]";
  rxn = RxnSmartsToChemicalReaction(smi); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==1);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  reacts.clear();
  smi = "OCC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);

  reacts.push_back(ROMOL_SPTR(mol));
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][0].get())));

  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==3);
  TEST_ASSERT(prod->getBondBetweenAtoms(0,1)->getBondType()==Bond::SINGLE);

  reacts.clear();
  smi = "O=CC";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);

  reacts.push_back(ROMOL_SPTR(mol));
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  MolOps::sanitizeMol(*(static_cast<RWMol *>(prods[0][0].get())));

  prod = prods[0][0];
  TEST_ASSERT(prod->getNumAtoms()==3);
  TEST_ASSERT(prod->getBondBetweenAtoms(0,1)->getBondType()==Bond::SINGLE);
  delete rxn;


  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test21Issue2540021(){
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing sf.net Issue 2540021: bad handling of atoms with explicit Hs." << std::endl;

  {
    std::string smi  = "[#7;!H0:1]>>[#7:1]C";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);

    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "C1=CNC=C1";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    rxn->initReactantMatchers();

    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);

    ROMOL_SPTR prod = prods[0][0];
    MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
    TEST_ASSERT(prod->getNumAtoms()==6);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getAtomicNum()==7);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getImplicitValence()==0);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getExplicitValence()==3);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getNoImplicit()==false);

    delete rxn;
  }

  {
    std::string smi="[c:1]1[c:2][n;H1:3][c:4][n:5]1>>[c:1]1[c:2][n:3][c:4](C)[n:5]1";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);

    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "C1=CNC=N1";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    rxn->initReactantMatchers();

    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);

    ROMOL_SPTR prod = prods[0][0];
    MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
    TEST_ASSERT(prod->getNumAtoms()==6);
    TEST_ASSERT(prod->getAtomWithIdx(2)->getAtomicNum()==7);
    TEST_ASSERT(prod->getAtomWithIdx(2)->getNumExplicitHs()==1);
    TEST_ASSERT(prod->getAtomWithIdx(5)->getAtomicNum()==7);
    TEST_ASSERT(prod->getAtomWithIdx(5)->getNumExplicitHs()==0);

    delete rxn;
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test22DotsToRemoveBonds(){
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing using dots in the products to remove bonds." << std::endl;

  {
    std::string smi  = "[C:1]1[O:2][N:3]1>>[C:1]1[O:2].[N:3]1";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();

    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "C1ON1";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);

    ROMOL_SPTR prod = prods[0][0];
    MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
    TEST_ASSERT(prod->getNumAtoms()==3);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getAtomicNum()==6);
    TEST_ASSERT(prod->getAtomWithIdx(1)->getAtomicNum()==8);
    TEST_ASSERT(prod->getAtomWithIdx(2)->getAtomicNum()==7);
    TEST_ASSERT(prod->getBondBetweenAtoms(0,1));
    TEST_ASSERT(prod->getBondBetweenAtoms(0,2));
    TEST_ASSERT(!prod->getBondBetweenAtoms(1,2));

    delete rxn;
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test23Pickling(){
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing pickling and depickling reactions." << std::endl;

  {
    std::string smi;
    ChemicalReaction *rxn; 
    MOL_SPTR_VECT reacts;
    std::vector<MOL_SPTR_VECT> prods;

    smi="[C:1]1[O:2][N:3]1>>[C:1]1[O:2].[N:3]1";
    rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();

    std::string pkl;
    ReactionPickler::pickleReaction(rxn,pkl);
    delete rxn;
    rxn = new ChemicalReaction();
    ReactionPickler::reactionFromPickle(pkl,rxn);
    rxn->initReactantMatchers();
    
    reacts.clear();
    smi = "C1ON1";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);

    ROMOL_SPTR prod = prods[0][0];
    MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
    TEST_ASSERT(prod->getNumAtoms()==3);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getAtomicNum()==6);
    TEST_ASSERT(prod->getAtomWithIdx(1)->getAtomicNum()==8);
    TEST_ASSERT(prod->getAtomWithIdx(2)->getAtomicNum()==7);
    TEST_ASSERT(prod->getBondBetweenAtoms(0,1));
    TEST_ASSERT(prod->getBondBetweenAtoms(0,2));
    TEST_ASSERT(!prod->getBondBetweenAtoms(1,2));

    // test construction from a pickle:
    delete rxn;
    rxn = new ChemicalReaction(pkl);
    rxn->initReactantMatchers();
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    prod = prods[0][0];
    MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
    TEST_ASSERT(prod->getNumAtoms()==3);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getAtomicNum()==6);
    TEST_ASSERT(prod->getAtomWithIdx(1)->getAtomicNum()==8);
    TEST_ASSERT(prod->getAtomWithIdx(2)->getAtomicNum()==7);
    TEST_ASSERT(prod->getBondBetweenAtoms(0,1));
    TEST_ASSERT(prod->getBondBetweenAtoms(0,2));
    TEST_ASSERT(!prod->getBondBetweenAtoms(1,2));
    
    delete rxn;
  }

  {
    std::string rdbase = getenv("RDBASE");
    std::string fName;
    std::string smi;
    ChemicalReaction *rxn;
    MOL_SPTR_VECT reacts;
    std::vector<MOL_SPTR_VECT> prods;

    fName = rdbase + "/Code/GraphMol/ChemReactions/testData/cyclization1.rxn";
    rxn = RxnFileToChemicalReaction(fName); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);

    std::string pkl;
    ReactionPickler::pickleReaction(rxn,pkl);
    delete rxn;
    rxn = new ChemicalReaction();
    ReactionPickler::reactionFromPickle(pkl,rxn);
    rxn->initReactantMatchers();

    smi = "OC(=O)CN";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    smi = "OC(=O)CN";    
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
  
    rxn->initReactantMatchers();
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
    TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test24AtomFlags(){
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing preservation of atom flags from rxn files." << std::endl;

  std::string rdbase = getenv("RDBASE");
  std::string fName;
  unsigned int nWarn,nError;

  {
  
    fName = rdbase + "/Code/GraphMol/ChemReactions/testData/atomflags.rxn";
    ChemicalReaction *rxn = RxnFileToChemicalReaction(fName); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);
    TEST_ASSERT(rxn->beginReactantTemplates()->get()->getAtomWithIdx(0)->hasProp("molAtomMapNumber"));
    TEST_ASSERT((++(rxn->beginReactantTemplates()))->get()->getAtomWithIdx(0)->hasProp("molAtomMapNumber"));
    TEST_ASSERT((++(rxn->beginReactantTemplates()))->get()->getAtomWithIdx(1)->hasProp("molAtomMapNumber"));
    
    delete rxn;
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test25Conformers(){
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing transfer of conformer data from reactants->products." << std::endl;

  unsigned int nWarn,nError;

  {
    std::string smi;
    smi="[C:1]=[O:2].[N:3]>>[O:2]=[C:1][N:3]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);

    ROMol *mol;
    Conformer *conf;
    MOL_SPTR_VECT reacts;
    std::vector<MOL_SPTR_VECT> prods;

    reacts.clear();
    smi = "C(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    conf=new Conformer(3);
    conf->setAtomPos(0,RDGeom::Point3D(1,0,0));
    conf->setAtomPos(1,RDGeom::Point3D(1,1,0));
    conf->setAtomPos(2,RDGeom::Point3D(1,0,1));
    mol->addConformer(conf,true);
    reacts.push_back(ROMOL_SPTR(mol));

    smi = "CN";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    conf=new Conformer(2);
    conf->setAtomPos(0,RDGeom::Point3D(-1,0,0));
    conf->setAtomPos(1,RDGeom::Point3D(-1,1,0));
    mol->addConformer(conf,true);
    reacts.push_back(ROMOL_SPTR(mol));

    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumConformers()==1);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).x==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).y==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).x==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).x==-1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).y==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).x==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).z==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).x==-1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).z==0.0);

    // test when only the first reactant has a conf:
    reacts.clear();
    smi = "C(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    conf=new Conformer(3);
    conf->setAtomPos(0,RDGeom::Point3D(1,0,0));
    conf->setAtomPos(1,RDGeom::Point3D(1,1,0));
    conf->setAtomPos(2,RDGeom::Point3D(1,0,1));
    mol->addConformer(conf,true);
    reacts.push_back(ROMOL_SPTR(mol));

    smi = "CN";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumConformers()==1);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).x==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).y==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).x==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).x==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).x==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).z==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).x==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).z==0.0);

    // test when only the second reactant has a conf:
    reacts.clear();
    smi = "C(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    smi = "CN";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    conf=new Conformer(2);
    conf->setAtomPos(0,RDGeom::Point3D(-1,0,0));
    conf->setAtomPos(1,RDGeom::Point3D(-1,1,0));
    mol->addConformer(conf,true);
    reacts.push_back(ROMOL_SPTR(mol));

    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumConformers()==1);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).x==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(0).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).x==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(1).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).x==-1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).y==1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(2).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).x==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(3).z==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).x==-1.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).y==0.0);
    TEST_ASSERT(prods[0][0]->getConformer().getAtomPos(4).z==0.0);
    
    // and, of course, when neither has a conformer:
    reacts.clear();
    smi = "C(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    smi = "CN";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==5);
    TEST_ASSERT(prods[0][0]->getNumConformers()==0);

    delete rxn;
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}



void test26V3000MDLParser(){
  ROMol *mol=0;
  ChemicalReaction *rxn;
  MOL_SPTR_VECT reacts;
  std::vector<MOL_SPTR_VECT> prods;
  std::string smi;
    
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing v3000 MDL parser" << std::endl;

  std::string rdbase = getenv("RDBASE");
  std::string fName;
  
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/v3k.AmideBond.rxn";

  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  smi = "C(=O)O";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
  TEST_ASSERT(prods[0][0]->getNumBonds()==3);


  delete rxn;
  reacts.clear();
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/v3k.cyclization1.rxn";
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);


  smi = "OC(=O)CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "OC(=O)CN";    
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  
  delete rxn;
  reacts.clear();
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/v3k.cyclization1.rxn";
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);


  smi = "OC(=O)CN";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));

  smi = "OC(=O)CN";    
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==1);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
  TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  
  delete rxn;
  reacts.clear();
  fName = rdbase + "/Code/GraphMol/ChemReactions/testData/v3k.cyclization2.rxn";
  rxn = RxnFileToChemicalReaction(fName); 
  TEST_ASSERT(rxn);
  TEST_ASSERT(rxn->getNumReactantTemplates()==2);
  TEST_ASSERT(rxn->getNumProductTemplates()==1);

  smi = "CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "C=CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  rxn->initReactantMatchers();
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==7);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));
  
  reacts.clear();
  smi = "CC=C[Cl]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "[F]C=CC=C[Br]";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==10);
  for(unsigned int i=0;i<prods.size();i++){
    unsigned int nDifferent=0;
    for(unsigned int j=0;j<prods.size();j++){
      if(MolToSmiles(*prods[i][0])!=MolToSmiles(*prods[j][0])) nDifferent += 1;
    }
    TEST_ASSERT(nDifferent==2);
  }

  reacts.clear();
  smi = "C1C=CCCC1";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
    
  smi = "C=CC=C";
  mol = SmilesToMol(smi);
  TEST_ASSERT(mol);
  reacts.push_back(ROMOL_SPTR(mol));
  
  prods = rxn->runReactants(reacts);
  TEST_ASSERT(prods.size()==4);
  TEST_ASSERT(prods[0].size()==1);
  TEST_ASSERT(prods[0][0]->getNumAtoms()==10);
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[1][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[2][0]));
  TEST_ASSERT(MolToSmiles(*prods[0][0])==MolToSmiles(*prods[3][0]));
  
  delete rxn;
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}



void test27SmartsWriter(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing reaction SMARTS writer." << std::endl;

  unsigned int nWarn,nError;

  {
    std::string smi;
    smi="[C:1]=[O:2].[N:3]>>[O:2]=[C:1]~[N:3]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);

    smi = ChemicalReactionToRxnSmarts(*rxn);
    TEST_ASSERT(smi=="[C:1]=[O:2].[N:3]>>[O:2]=[C:1]~[N:3]");

    delete rxn;
    rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test28RxnDepictor(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing reaction depictor." << std::endl;

  unsigned int nWarn,nError;

  {
    std::string smi;
    smi="[C:10]1[C:11][C:12]1[C:1]=[O:2].[N:3][C:20]([C:21])[C:22]>>[O:2]=[C:1]([C:10]1[C:11][C:12]1)[N:3][C:20]([C:21])[C:22]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);

    for(RDKit::MOL_SPTR_VECT::const_iterator templIt=rxn->beginReactantTemplates();
        templIt!=rxn->endReactantTemplates();++templIt){
      TEST_ASSERT((*templIt)->getNumConformers()==0);
    }
    for(RDKit::MOL_SPTR_VECT::const_iterator templIt=rxn->beginProductTemplates();
        templIt!=rxn->endProductTemplates();++templIt){
      TEST_ASSERT((*templIt)->getNumConformers()==0);
    }

    RDDepict::compute2DCoordsForReaction(*rxn);
    for(RDKit::MOL_SPTR_VECT::const_iterator templIt=rxn->beginReactantTemplates();
        templIt!=rxn->endReactantTemplates();++templIt){
      TEST_ASSERT((*templIt)->getNumConformers()==1);
      TEST_ASSERT(!(*templIt)->getConformer().is3D());
    }
    for(RDKit::MOL_SPTR_VECT::const_iterator templIt=rxn->beginProductTemplates();
        templIt!=rxn->endProductTemplates();++templIt){
      TEST_ASSERT((*templIt)->getNumConformers()==1);
      TEST_ASSERT(!(*templIt)->getConformer().is3D());
    }
  }
  { // make sure the depiction doesn't screw up the reaction itself
    std::string rdbase = getenv("RDBASE");
    std::string fName;
    std::string smi;
    ChemicalReaction *rxn;
    MOL_SPTR_VECT reacts;
    std::vector<MOL_SPTR_VECT> prods;

    fName = rdbase + "/Code/GraphMol/ChemReactions/testData/cyclization1.rxn";
    rxn = RxnFileToChemicalReaction(fName); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);

    RDDepict::compute2DCoordsForReaction(*rxn);

    smi = "OC(=O)CN";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));

    smi = "OC(=O)CN";    
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
  
    rxn->initReactantMatchers();
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==8);
    TEST_ASSERT(MolToSmiles(*prods[0][0])=="O=C1CNC(=O)CN1");
  }


  {
    std::string smi  = "[#7;!H0:1]>>[#7:1]C";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);

    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "C1=CNC=C1";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    RDDepict::compute2DCoordsForReaction(*rxn);

    rxn->initReactantMatchers();

    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);

    ROMOL_SPTR prod = prods[0][0];
    MolOps::sanitizeMol(*(static_cast<RWMol *>(prod.get())));
    TEST_ASSERT(prod->getNumAtoms()==6);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getAtomicNum()==7);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getImplicitValence()==0);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getExplicitValence()==3);
    TEST_ASSERT(prod->getAtomWithIdx(0)->getNoImplicit()==false);

    delete rxn;
  }

  
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test29RxnWriter(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing RXN file writer." << std::endl;

  unsigned int nWarn,nError;

  {
    std::string rdbase = getenv("RDBASE");
    std::string fName;
    std::string smi;
  
    fName = rdbase + "/Code/GraphMol/ChemReactions/testData/AmideBond.rxn";
    ChemicalReaction *rxn = RxnFileToChemicalReaction(fName); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);

    smi = ChemicalReactionToRxnSmarts(*rxn);
    TEST_ASSERT(smi=="[#6:2](-[#8])=[#8:1].[#7:3]>>[#7:3]-[#6:2]=[#8:1]")

    std::string mb;
    mb=ChemicalReactionToRxnBlock(*rxn);

    delete rxn;
    rxn = RxnBlockToChemicalReaction(mb); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);
  }
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test30ReactProdQueries(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing reactant and product queries." << std::endl;

  {
    ROMol *mol;
    unsigned int nWarn,nError,which;
    std::string smi;
    smi="[c;H:1]:[c:2](:[c;H:3])Br.[C:4](=[O:5])Cl>>[c:1]:[c:2]([c:3])-[C:4]=[O:5]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);

    smi = "c1ccccc1Br";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(isMoleculeReactantOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==0);
    delete(mol);

    smi = "c1ccccc1Cl";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(!isMoleculeReactantOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==rxn->getNumReactantTemplates());
    delete(mol);

    smi = "c1ccncc1Br";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(isMoleculeReactantOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==0);
    delete(mol);

    smi = "c1cccnc1Br";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(!isMoleculeReactantOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==rxn->getNumReactantTemplates());
    delete(mol);

    smi = "c1cccc(C)c1Br";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(!isMoleculeReactantOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==rxn->getNumReactantTemplates());
    delete(mol);

    smi = "ClC(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(isMoleculeReactantOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==1);
    delete(mol);

    smi = "C(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(!isMoleculeReactantOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==rxn->getNumReactantTemplates());
    delete(mol);

    smi = "c1ccccc1C(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(isMoleculeProductOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==0);
    delete(mol);

    smi = "c1cccnc1C(=O)C";
    mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    TEST_ASSERT(!isMoleculeProductOfReaction(*rxn,*mol,which));
    TEST_ASSERT(which==rxn->getNumProductTemplates());
    delete(mol);

    delete(rxn);
  }
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test31Issue3140490(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing Issue 3140490." << std::endl;

  {
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1]>>[N:1]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);


    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "OC";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(!prods[0][0]->getAtomWithIdx(0)->hasProp("molAtomMapNumber"));
    TEST_ASSERT(!prods[0][0]->getAtomWithIdx(1)->hasProp("molAtomMapNumber"));
    delete(rxn);
  }
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test32Replacements(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing string replacement in parsing." << std::endl;

  {
    std::map<std::string,std::string> repls;
    repls["{amine}"]="$([N;!H0;$(N-[#6]);!$(N-[!#6;!#1]);!$(N-C=[O,N,S])])";
    unsigned int nWarn,nError;
    std::string smi;
    smi="[{amine}:1]>>[*:1]-C";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi,&repls); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);

    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "CCN";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==4);
    delete(rxn);
  }
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test33ReactingAtoms1(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing getReactingAtoms() 1." << std::endl;

  { // basics
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1][C:2]>>[N:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==1);
  }
  { // no changes
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1][C:2]>>[O:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // make sure atomic number queries work:
    unsigned int nWarn,nError;
    std::string smi;
    smi="[#8:1][C:2]>>[O:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // query in the reactants, dummy in product
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O,N:1][C:2]>>[*:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }

  { // recursive query in the reactants without an atomic number query
    unsigned int nWarn,nError;
    std::string smi;
    smi="[$(O):1][C:2]>>[O:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==1);
  }
  { // recursive query with atomic number query
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O;$(O):1][C:2]>>[O:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // recursive query with atomic number query, alternate ordering
    // FIX: this returns a changed atom (since we don't know the atomic
    // number of the atom) but probably shouldn't
    unsigned int nWarn,nError;
    std::string smi;
    smi="[$(O);O:1][C:2]>>[O:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==1);
  }
  { // recursive query in the reactants, dummy in products
    unsigned int nWarn,nError;
    std::string smi;
    smi="[$(O):1][C:2]>>[*:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // query with degree/H info in the reactants:
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O;H1:1][C:2]>>[O:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // dummy in the reactants, dummy in products
    unsigned int nWarn,nError;
    std::string smi;
    smi="[*:1][C:2]>>[*:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // two reactants, one changes
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1][C:2].[N:3]>>[N:1][C:2].[N:3]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==2);
    TEST_ASSERT(ratoms[0].size()==1);
    TEST_ASSERT(ratoms[1].size()==0);
  }
  { // two reactants, one changes, reordered
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1][C:2].[N:3]>>[N:3].[N:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==2);
    TEST_ASSERT(ratoms[0].size()==1);
    TEST_ASSERT(ratoms[1].size()==0);
  }
  { // dummies for duplicating atom properties
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1][C:2].[N:3]>>[N:1][C:2].[*:3]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==2);
    TEST_ASSERT(ratoms[0].size()==1);
    TEST_ASSERT(ratoms[1].size()==0);
  }
  { // query in the reactants, dummy in products
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O,N:1][C:2]>>[*:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // changed degree
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1][C:2].[N:3]>>[N:1][C:2].[*:3]C";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==2);
    TEST_ASSERT(ratoms[0].size()==1);
    TEST_ASSERT(ratoms[1].size()==1);
  }
  { // unmapped atoms in reactants:
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1]C>>[O:1]C";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==2);
  }
  { // don't return info about unmapped atoms:
    unsigned int nWarn,nError;
    std::string smi;
    smi="[O:1]C>>[O:1]C";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn,true);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==1);
  }
  { // changing atom order
    unsigned int nWarn,nError;
    std::string smi;
    smi="[C:1]-[C:2]>>[C:2]-[C:1]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // changing bond order
    unsigned int nWarn,nError;
    std::string smi;
    smi="[C:1]-[C:2]>>[C:1]=[C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==2);
  }
  { // changing bond orders
    unsigned int nWarn,nError;
    std::string smi;
    smi="[C:1]-[C:2]=[C:3]>>[C:1]=[C:2]-[C:3]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==3);
  }
  { // query bond order
    unsigned int nWarn,nError;
    std::string smi;
    smi="[C:1]-[C:2]>>[C:1]~[C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==0);
  }
  { // changing connectivity
    unsigned int nWarn,nError;
    std::string smi;
    smi="[C:1]-[C:2]-[C:3]>>[C:1]~[C:3]~[C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==3);
  }
  { // changing connectivity 2
    unsigned int nWarn,nError;
    std::string smi;
    smi="[C:1]1[C:2][C:3]1>>[C:1][C:2][C:3]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==1);
    TEST_ASSERT(ratoms[0].size()==2);
  }
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test34ReactingAtoms2(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing getReactingAtoms() 2" << std::endl;

  {
    std::string rdbase = getenv("RDBASE");
    std::string fName = rdbase + "/Code/GraphMol/ChemReactions/testData/AmideBond.rxn";
    ChemicalReaction *rxn = RxnFileToChemicalReaction(fName); 
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==2);
    TEST_ASSERT(ratoms[0].size()==2);
    TEST_ASSERT(ratoms[1].size()==1);
  }
  {
    std::string rdbase = getenv("RDBASE");
    std::string fName = rdbase + "/Code/GraphMol/ChemReactions/testData/cyclization1.rxn";
    ChemicalReaction *rxn = RxnFileToChemicalReaction(fName); 
    TEST_ASSERT(rxn);
    rxn->initReactantMatchers();

    VECT_INT_VECT ratoms=getReactingAtoms(*rxn);
    TEST_ASSERT(ratoms.size()==2);
    TEST_ASSERT(ratoms[0].size()==3);
    TEST_ASSERT(ratoms[1].size()==3);
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test35ParensInReactants1(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing grouping parens in reactants1" << std::endl;

  { 
    std::string smi="[C:1].[C:2]>>[C:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    delete rxn;
  }

  { 
    std::string smi="([C:1].[C:2])>>[C:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    delete rxn;
  }
  { 
    std::string smi="([C:1].C(=O)O).[C:2]>>[C:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    delete rxn;
  }

  { 
    std::string smi="[C:1](=O)O.[C:2]>>[C:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    delete rxn;
  }

  { 
    std::string smi="[C:1](=O)O.([C:2])>>[C:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    delete rxn;
  }
  { 
    std::string smi="[C:1](=O)O.([C:2].N)>>[C:1][C:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==2);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    delete rxn;
  }
  { 
    std::string smi="([C:1](=O)O.[C:2]>>[C:1][C:2]";
    ChemicalReaction *rxn=0;
    try{
      rxn = RxnSmartsToChemicalReaction(smi);
    } catch (const ChemicalReactionParserException &e){
      rxn=0;
    }
    TEST_ASSERT(!rxn);
  }
  { 
    std::string smi="[C:1](=O)O.([C:2]>>[C:1][C:2]";
    ChemicalReaction *rxn=0;
    try{
      rxn = RxnSmartsToChemicalReaction(smi);
    } catch (const ChemicalReactionParserException &e){
      rxn=0;
    }
    TEST_ASSERT(!rxn);
  }
  { 
    std::string smi="[C:1](=O)O).[C:2]>>[C:1][C:2]";
    ChemicalReaction *rxn=0;
    try{
      rxn = RxnSmartsToChemicalReaction(smi);
    } catch (const ChemicalReactionParserException &e){
      rxn=0;
    }
    TEST_ASSERT(!rxn);
  }
  { 
    std::string smi="[C:1](=O)O.[C:2])>>[C:1][C:2]";
    ChemicalReaction *rxn=0;
    try{
      rxn = RxnSmartsToChemicalReaction(smi);
    } catch (const ChemicalReactionParserException &e){
      rxn=0;
    }
    TEST_ASSERT(!rxn);
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test36ParensInReactants2(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing grouping parens in reactants2" << std::endl;

  { 
    std::string smi="([C:1].[O:2])>>[C:1][O:2]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi);
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "CNO";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[0][0]->getNumAtoms()==3);
    TEST_ASSERT(prods[0][0]->getNumBonds()==3);

    delete rxn;
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test37ProtectOption(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing use of _protected property on atoms." << std::endl;

  {
    unsigned int nWarn,nError;
    std::string smi="[O:1]>>[N:1]";
    ChemicalReaction *rxn = RxnSmartsToChemicalReaction(smi); 
    TEST_ASSERT(rxn);
    TEST_ASSERT(rxn->getNumReactantTemplates()==1);
    TEST_ASSERT(rxn->getNumProductTemplates()==1);
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);


    MOL_SPTR_VECT reacts;
    reacts.clear();
    smi = "OCO";
    ROMol *mol = SmilesToMol(smi);
    TEST_ASSERT(mol);
    reacts.push_back(ROMOL_SPTR(mol));
    std::vector<MOL_SPTR_VECT> prods;
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==2);
    TEST_ASSERT(prods[0].size()==1);
    TEST_ASSERT(prods[1].size()==1);

    reacts[0]->getAtomWithIdx(0)->setProp("_protected",1);
    prods = rxn->runReactants(reacts);
    TEST_ASSERT(prods.size()==1);
    TEST_ASSERT(prods[0].size()==1);
    
    delete(rxn);
  }
  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}

void test38AddRecursiveQueriesToReaction(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing use of adding recursive queries to a reaction." << std::endl;

  {
    ROMol *mol=0;
    ChemicalReaction rxn;
    MOL_SPTR_VECT reacts;
    std::string smi;

    smi = "[C:1](=[O:2])";
    mol = SmartsToMol(smi);
    mol->getAtomWithIdx(0)->setProp("replaceme", "foo");
    TEST_ASSERT(mol);
    rxn.addReactantTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumReactantTemplates()==1);

    smi = "[N:3][C:4]";
    mol = SmartsToMol(smi);
    TEST_ASSERT(mol);
    rxn.addReactantTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumReactantTemplates()==2);

    smi = "[C:1](=[O:2])[N:3][C:4]";
    mol = SmartsToMol(smi);
    TEST_ASSERT(mol);
    rxn.addProductTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumProductTemplates()==1);

    std::string smi2="CCl";
    ROMOL_SPTR q1(SmilesToMol(smi2));
    std::map<std::string,ROMOL_SPTR> mp;
    mp["foo"]=q1;

    bool ok=false;
    try {
      addRecursiveQueriesToReaction(rxn, mp, "replaceme");
    } catch (ChemicalReactionException &e) {
      ok=true;
    }
    TEST_ASSERT(ok);

    rxn.initReactantMatchers();
    addRecursiveQueriesToReaction(rxn, mp, "replaceme");
    MatchVectType mv;
    std::string msmi="C(=O)Cl";
    ROMol *mmol=SmilesToMol(msmi);
    TEST_ASSERT(SubstructMatch(*mmol, *(*(rxn.beginReactantTemplates())), mv));
    delete mmol;
    msmi="C(=O)O";
    mmol=SmilesToMol(msmi);
    TEST_ASSERT(!SubstructMatch(*mmol, *(*(rxn.beginReactantTemplates())), mv));
    delete mmol;
  }

  {
    ROMol *mol=0;
    ChemicalReaction rxn;
    MOL_SPTR_VECT reacts;
    std::string smi;

    smi = "[C:1](=[O:2])";
    mol = SmartsToMol(smi);
    mol->getAtomWithIdx(0)->setProp("replaceme", "foo");
    TEST_ASSERT(mol);
    rxn.addReactantTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumReactantTemplates()==1);

    smi = "[N:3][C:4]";
    mol = SmartsToMol(smi);
    TEST_ASSERT(mol);
    rxn.addReactantTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumReactantTemplates()==2);

    smi = "[C:1](=[O:2])[N:3][C:4]";
    mol = SmartsToMol(smi);
    TEST_ASSERT(mol);
    rxn.addProductTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumProductTemplates()==1);

    std::string smi2="CO";
    ROMOL_SPTR q1(SmilesToMol(smi2));
    std::map<std::string,ROMOL_SPTR> mp;
    mp["foo"]=q1;

    rxn.initReactantMatchers();
    std::vector<std::vector<std::pair<unsigned int, std::string> > > labels;
    addRecursiveQueriesToReaction(rxn, mp, "replaceme", &labels);
    TEST_ASSERT(labels.size()==2);
    TEST_ASSERT(labels[0][0].second=="foo");
  }

  {
    ROMol *mol=0;
    ChemicalReaction rxn;
    MOL_SPTR_VECT reacts;
    std::string smi;

    smi = "[N:3][C:4]";
    mol = SmartsToMol(smi);
    TEST_ASSERT(mol);
    rxn.addReactantTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumReactantTemplates()==1);

    smi = "[C:1](=[O:2])";
    mol = SmartsToMol(smi);
    mol->getAtomWithIdx(0)->setProp("replaceme", "foo");
    TEST_ASSERT(mol);
    rxn.addReactantTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumReactantTemplates()==2);

    smi = "[C:1](=[O:2])[N:3][C:4]";
    mol = SmartsToMol(smi);
    TEST_ASSERT(mol);
    rxn.addProductTemplate(ROMOL_SPTR(mol));
    TEST_ASSERT(rxn.getNumProductTemplates()==1);

    std::string smi2="CO";
    ROMOL_SPTR q1(SmilesToMol(smi2));
    std::map<std::string,ROMOL_SPTR> mp;
    mp["foo"]=q1;

    rxn.initReactantMatchers();
    std::vector<std::vector<std::pair<unsigned int, std::string> > > labels;
    addRecursiveQueriesToReaction(rxn, mp, "replaceme", &labels);
    TEST_ASSERT(labels.size()==2);
    TEST_ASSERT(labels[1][0].second=="foo");
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


void test39InnocentChiralityLoss(){
  BOOST_LOG(rdInfoLog) << "-------------------------------------" << std::endl;
  BOOST_LOG(rdInfoLog) << "Testing loss of chirality on innocent atoms." << std::endl;

  {
    ChemicalReaction *rxn=RxnSmartsToChemicalReaction("[C:2][C:1]=O>>[C:2][C:1]=S");
    unsigned int nWarn,nError;
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);
    
    {
      std::string smi = "Cl[C@H](F)C=O";
      ROMol *mol = SmilesToMol(smi);
      MOL_SPTR_VECT reacts;
      reacts.push_back(ROMOL_SPTR(mol));
      std::vector<MOL_SPTR_VECT> prods;
      prods = rxn->runReactants(reacts);
      TEST_ASSERT(prods.size()==1);
      TEST_ASSERT(prods[0].size()==1);
      smi=MolToSmiles(*prods[0][0]);
      TEST_ASSERT(smi=="FC(Cl)C=S");
      smi=MolToSmiles(*prods[0][0],true);
      TEST_ASSERT(smi=="F[C@@H](Cl)C=S");
    }
    {
      std::string smi = "O=C[C@@H](F)Cl";
      ROMol *mol = SmilesToMol(smi);
      MOL_SPTR_VECT reacts;
      reacts.push_back(ROMOL_SPTR(mol));
      std::vector<MOL_SPTR_VECT> prods;
      prods = rxn->runReactants(reacts);
      TEST_ASSERT(prods.size()==1);
      TEST_ASSERT(prods[0].size()==1);
      smi=MolToSmiles(*prods[0][0]);
      TEST_ASSERT(smi=="FC(Cl)C=S");
      smi=MolToSmiles(*prods[0][0],true);
      TEST_ASSERT(smi=="F[C@@H](Cl)C=S");
    }
    {
      std::string smi = "F[C@H](C=O)Cl";
      ROMol *mol = SmilesToMol(smi);
      MOL_SPTR_VECT reacts;
      reacts.push_back(ROMOL_SPTR(mol));
      std::vector<MOL_SPTR_VECT> prods;
      prods = rxn->runReactants(reacts);
      TEST_ASSERT(prods.size()==1);
      TEST_ASSERT(prods[0].size()==1);
      smi=MolToSmiles(*prods[0][0]);
      TEST_ASSERT(smi=="FC(Cl)C=S");
      smi=MolToSmiles(*prods[0][0],true);
      TEST_ASSERT(smi=="F[C@@H](Cl)C=S");
    }
    delete rxn;
  }


  {
    // in this case the atom isn't actually innocent, but we can handle it anyway because
    // only one bond changes
    ChemicalReaction *rxn=RxnSmartsToChemicalReaction("[C:1]-O>>[C:1]-S");
    unsigned int nWarn,nError;
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);
    
    {
      std::string smi = "Cl[C@H](F)O";
      ROMol *mol = SmilesToMol(smi);
      MOL_SPTR_VECT reacts;
      reacts.push_back(ROMOL_SPTR(mol));
      std::vector<MOL_SPTR_VECT> prods;
      prods = rxn->runReactants(reacts);
      TEST_ASSERT(prods.size()==1);
      TEST_ASSERT(prods[0].size()==1);
      smi=MolToSmiles(*prods[0][0]);
      TEST_ASSERT(smi=="FC(S)Cl");
      smi=MolToSmiles(*prods[0][0],true);
      TEST_ASSERT(smi=="F[C@H](S)Cl");
    }
    delete rxn;
  }
  {
    // another non-innocent atom
    ChemicalReaction *rxn=RxnSmartsToChemicalReaction("[C:1]-O>>[C:1]");
    unsigned int nWarn,nError;
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);
    
    {
      std::string smi = "Cl[C@H](F)O";
      ROMol *mol = SmilesToMol(smi);
      MOL_SPTR_VECT reacts;
      reacts.push_back(ROMOL_SPTR(mol));
      std::vector<MOL_SPTR_VECT> prods;
      prods = rxn->runReactants(reacts);
      TEST_ASSERT(prods.size()==1);
      TEST_ASSERT(prods[0].size()==1);
      smi=MolToSmiles(*prods[0][0]);
      TEST_ASSERT(smi=="FCCl");
      smi=MolToSmiles(*prods[0][0],true);
      TEST_ASSERT(smi=="FCCl");
    }
    delete rxn;
  }
  {
    // one of the original bug report cases:
    ChemicalReaction *rxn=RxnSmartsToChemicalReaction("[C:1](=[O:2])[C:3][C:4]([OH:5])[#6:6]>>[C:1](=[O:2])[C:3][H].[C:4](=[O:5])[#6:6]");
    unsigned int nWarn,nError;
    rxn->initReactantMatchers();
    TEST_ASSERT(rxn->validate(nWarn,nError,false));
    TEST_ASSERT(nWarn==0);
    TEST_ASSERT(nError==0);
    
    {
      std::string smi = "CC(O)[C@](N)(F)C(C)=O";
      ROMol *mol = SmilesToMol(smi);
      MOL_SPTR_VECT reacts;
      reacts.push_back(ROMOL_SPTR(mol));
      std::vector<MOL_SPTR_VECT> prods;
      prods = rxn->runReactants(reacts);
      TEST_ASSERT(prods.size()==1);
      TEST_ASSERT(prods[0].size()==2);
      smi=MolToSmiles(*prods[0][0]);
      TEST_ASSERT(smi=="[H]C(N)(F)C(C)=O");
      smi=MolToSmiles(*prods[0][0],true);
      TEST_ASSERT(smi=="[H][C@](N)(F)C(C)=O");
    }
    delete rxn;
  }

  BOOST_LOG(rdInfoLog) << "\tdone" << std::endl;
}


int main() { 
  RDLog::InitLogs();
    
  BOOST_LOG(rdInfoLog) << "********************************************************\n";
  BOOST_LOG(rdInfoLog) << "Testing Chemical Reactions \n";

#if 1
  test1Basics();
  test2SimpleReactions();
  test3RingFormation();
  test4MultipleProducts();
  test5Salts();
  test6DaylightParser();
  test7MDLParser();
  test8Validation();
  test9ProductQueries();
  test10ChiralityDaylight();
  test11ChiralityRxn();
  test12DoubleBondStereochem();
  test13Issue1748846();
  test14Issue1804420();
  test15Issue1882749();
  test16Exceptions();
  test17Issue1920627();
  test18PropertyTransfer();
  test19Issue2050085();
  test20BondQueriesInProduct();
  test21Issue2540021();
  test22DotsToRemoveBonds();
  test23Pickling();
  test24AtomFlags();
  test25Conformers();
  test26V3000MDLParser();
  test27SmartsWriter();
  test28RxnDepictor();
  test29RxnWriter();
  test30ReactProdQueries();
  test31Issue3140490();
  test32Replacements();

  test33ReactingAtoms1();
  test34ReactingAtoms2();
  test35ParensInReactants1();
  test36ParensInReactants2();
  test37ProtectOption();

  test38AddRecursiveQueriesToReaction();
#endif
  test39InnocentChiralityLoss();

  BOOST_LOG(rdInfoLog) << "*******************************************************\n";
  return(0);
}

