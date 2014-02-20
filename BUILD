// Rdkit
[
  { "config": {
      "component": "rdkit",
      "component_root": "Code",
      "licenses": [ "http://opensource.org/licenses/BSD-3-Clause" ]
  } },

  { "cmake": {
    "name": "rdkit_make",
    "cmake_args" : [ "-DBOOST_ROOT=$ROOT_DIR/$BOOST_ROOT",
                     "-DBOOST_INCLUDEDIR=$ROOT_DIR/$BOOST_INCLUDEDIR",
                     "-DBoost_NO_SYSTEM_PATHS=TRUE"
    ],
    "dependencies": [ "../boost:boost" ],
    "outs": [ "$GEN_DIR/lib/libAlignment_static.a",
              "$GEN_DIR/lib/libCatalogs_static.a",
              "$GEN_DIR/lib/libChemReactions_static.a",
              "$GEN_DIR/lib/libChemTransforms_static.a",
              "$GEN_DIR/lib/libChemicalFeatures_static.a",
              "$GEN_DIR/lib/libDataStructs_static.a",
              "$GEN_DIR/lib/libDepictor_static.a",
              "$GEN_DIR/lib/libDescriptors_static.a",
              "$GEN_DIR/lib/libDistGeomHelpers_static.a",
              "$GEN_DIR/lib/libDistGeometry_static.a",
              "$GEN_DIR/lib/libEigenSolvers_static.a",
              "$GEN_DIR/lib/libFileParsers_static.a",
              "$GEN_DIR/lib/libFingerprints_static.a",
              "$GEN_DIR/lib/libForceFieldHelpers_static.a",
              "$GEN_DIR/lib/libForceField_static.a",
              "$GEN_DIR/lib/libFragCatalog_static.a",
              "$GEN_DIR/lib/libGraphMol_static.a",
              "$GEN_DIR/lib/libMolAlign_static.a",
              "$GEN_DIR/lib/libMolCatalog_static.a",
              "$GEN_DIR/lib/libMolChemicalFeatures_static.a",
              "$GEN_DIR/lib/libMolTransforms_static.a",
              "$GEN_DIR/lib/libOptimizer_static.a",
              "$GEN_DIR/lib/libPartialCharges_static.a",
              "$GEN_DIR/lib/libRDBoost_static.a",
              "$GEN_DIR/lib/libRDGeneral_static.a",
              "$GEN_DIR/lib/libRDGeometryLib_static.a",
              "$GEN_DIR/lib/libSLNParse_static.a",
              "$GEN_DIR/lib/libShapeHelpers_static.a",
              "$GEN_DIR/lib/libSimDivPickers_static.a",
              "$GEN_DIR/lib/libSmilesParse_static.a",
              "$GEN_DIR/lib/libSubgraphs_static.a",
              "$GEN_DIR/lib/libSubstructMatch_static.a",
              "$GEN_DIR/lib/libhc_static.a"
    ]
  } },

  { "cc_library": {
    "name": "rdkit_headers",
    "cc_headers": [ "Code/*/*.h",
                    "Code/*/*/*.h",
                    "Code/*/*/*/*.h",
                    "Code/*/*/*/*/*.h"
    ],
    "header_compile_args": [ "-I$SRC_DIR/Code" ]
  } },

  { "cc_library": {
    "name": "Alignment",
    "cc_objects": [ "$GEN_DIR/lib/libAlignment_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "Catalogs",
    "cc_objects": [ "$GEN_DIR/lib/libCatalogs_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "ChemReactions",
    "cc_objects": [ "$GEN_DIR/lib/libChemReactions_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "ChemTransforms",
    "cc_objects": [ "$GEN_DIR/lib/libChemTransforms_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "ChemicalFeatures",
    "cc_objects": [ "$GEN_DIR/lib/libChemicalFeatures_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "DataStructs",
    "cc_objects": [ "$GEN_DIR/lib/libDataStructs_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "Depictor",
    "cc_objects": [ "$GEN_DIR/lib/libDepictor_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "Descriptors",
    "cc_objects": [ "$GEN_DIR/lib/libDescriptors_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "DistGeomHelpers",
    "cc_objects": [ "$GEN_DIR/lib/libDistGeomHelpers_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers", ":DistGeometry" ]
  } },
  { "cc_library": {
    "name": "DistGeometry",
    "cc_objects": [ "$GEN_DIR/lib/libDistGeometry_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "EigenSolvers",
    "cc_objects": [ "$GEN_DIR/lib/libEigenSolvers_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "FileParsers",
    "cc_objects": [ "$GEN_DIR/lib/libFileParsers_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "Fingerprints",
    "cc_objects": [ "$GEN_DIR/lib/libFingerprints_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "ForceFieldHelpers",
    "cc_objects": [ "$GEN_DIR/lib/libForceFieldHelpers_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers", ":ForceField" ]
  } },
  { "cc_library": {
    "name": "ForceField",
    "cc_objects": [ "$GEN_DIR/lib/libForceField_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "FragCatalog",
    "cc_objects": [ "$GEN_DIR/lib/libFragCatalog_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "GraphMol",
    "cc_objects": [ "$GEN_DIR/lib/libGraphMol_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "MolAlign",
    "cc_objects": [ "$GEN_DIR/lib/libMolAlign_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "MolCatalog",
    "cc_objects": [ "$GEN_DIR/lib/libMolCatalog_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "MolChemicalFeatures",
    "cc_objects": [ "$GEN_DIR/lib/libMolChemicalFeatures_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "MolTransforms",
    "cc_objects": [ "$GEN_DIR/lib/libMolTransforms_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "Optimizer",
    "cc_objects": [ "$GEN_DIR/lib/libOptimizer_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "PartialCharges",
    "cc_objects": [ "$GEN_DIR/lib/libPartialCharges_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "RDBoost",
    "cc_objects": [ "$GEN_DIR/lib/libRDBoost_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "RDGeneral",
    "cc_objects": [ "$GEN_DIR/lib/libRDGeneral_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "RDGeometryLib",
    "cc_objects": [ "$GEN_DIR/lib/libRDGeometryLib_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "SLNParse",
    "cc_objects": [ "$GEN_DIR/lib/libSLNParse_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "ShapeHelpers",
    "cc_objects": [ "$GEN_DIR/lib/libShapeHelpers_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "SimDivPickers",
    "cc_objects": [ "$GEN_DIR/lib/libSimDivPickers_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "SmilesParse",
    "cc_objects": [ "$GEN_DIR/lib/libSmilesParse_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "Subgraphs",
    "cc_objects": [ "$GEN_DIR/lib/libSubgraphs_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "SubstructMatch",
    "cc_objects": [ "$GEN_DIR/lib/libSubstructMatch_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },
  { "cc_library": {
    "name": "hc",
    "cc_objects": [ "$GEN_DIR/lib/libhc_static.a" ],
    "strict_file_mode": false,
    "dependencies": [ ":rdkit_make", ":rdkit_headers" ]
  } },

   // All of them.
  { "cc_library": {
    "name": "rdkit",
    "dependencies": [ ":Alignment",
                      ":Catalogs",
                      ":ChemReactions",
                      ":ChemTransforms",
                      ":ChemicalFeatures",
                      ":DataStructs",
                      ":Depictor",
                      ":Descriptors",
                      ":DistGeomHelpers",
                      ":DistGeometry",
                      ":EigenSolvers",
                      ":FileParsers",
                      ":Fingerprints",
                      ":ForceFieldHelpers",
                      ":ForceField",
                      ":FragCatalog",
                      ":GraphMol",
                      ":MolAlign",
                      ":MolCatalog",
                      ":MolChemicalFeatures",
                      ":MolTransforms",
                      ":Optimizer",
                      ":PartialCharges",
                      ":RDBoost",
                      ":RDGeneral",
                      ":RDGeometryLib",
                      ":SLNParse",
                      ":ShapeHelpers",
                      ":SimDivPickers",
                      ":SmilesParse",
                      ":Subgraphs",
                      ":SubstructMatch",
                      ":hc"
    ]
  } }
]