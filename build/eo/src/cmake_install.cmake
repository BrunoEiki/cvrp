# Install script for directory: /home/bruno/paradiseo/eo/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/bruno/paradiseo")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibrariesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/bruno/paradiseo/build/lib/libeo.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/paradiseo/eo" TYPE FILE FILES
    "/home/bruno/paradiseo/eo/src/EO.h"
    "/home/bruno/paradiseo/eo/src/PO.h"
    "/home/bruno/paradiseo/eo/src/apply.h"
    "/home/bruno/paradiseo/eo/src/eo"
    "/home/bruno/paradiseo/eo/src/eoAlgo.h"
    "/home/bruno/paradiseo/eo/src/eoAlgoFoundry.h"
    "/home/bruno/paradiseo/eo/src/eoAlgoFoundryEA.h"
    "/home/bruno/paradiseo/eo/src/eoAlgoFoundryFastGA.h"
    "/home/bruno/paradiseo/eo/src/eoAlgoReset.h"
    "/home/bruno/paradiseo/eo/src/eoAlgoRestart.h"
    "/home/bruno/paradiseo/eo/src/eoBinaryFlight.h"
    "/home/bruno/paradiseo/eo/src/eoBitParticle.h"
    "/home/bruno/paradiseo/eo/src/eoBreed.h"
    "/home/bruno/paradiseo/eo/src/eoCellularEasyEA.h"
    "/home/bruno/paradiseo/eo/src/eoCloneOps.h"
    "/home/bruno/paradiseo/eo/src/eoCombinedContinue.h"
    "/home/bruno/paradiseo/eo/src/eoCombinedInit.h"
    "/home/bruno/paradiseo/eo/src/eoConstrictedVariableWeightVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoConstrictedVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoContinue.h"
    "/home/bruno/paradiseo/eo/src/eoCounter.h"
    "/home/bruno/paradiseo/eo/src/eoCtrlCContinue.h"
    "/home/bruno/paradiseo/eo/src/eoDetSelect.h"
    "/home/bruno/paradiseo/eo/src/eoDetTournamentSelect.h"
    "/home/bruno/paradiseo/eo/src/eoDistribUpdater.h"
    "/home/bruno/paradiseo/eo/src/eoDistribution.h"
    "/home/bruno/paradiseo/eo/src/eoDualFitness.h"
    "/home/bruno/paradiseo/eo/src/eoEDA.h"
    "/home/bruno/paradiseo/eo/src/eoEasyEA.h"
    "/home/bruno/paradiseo/eo/src/eoEasyPSO.h"
    "/home/bruno/paradiseo/eo/src/eoEvalCmd.h"
    "/home/bruno/paradiseo/eo/src/eoEvalContinue.h"
    "/home/bruno/paradiseo/eo/src/eoEvalCounterThrowException.h"
    "/home/bruno/paradiseo/eo/src/eoEvalDump.h"
    "/home/bruno/paradiseo/eo/src/eoEvalFoundryEA.h"
    "/home/bruno/paradiseo/eo/src/eoEvalFoundryFastGA.h"
    "/home/bruno/paradiseo/eo/src/eoEvalFunc.h"
    "/home/bruno/paradiseo/eo/src/eoEvalFuncCounter.h"
    "/home/bruno/paradiseo/eo/src/eoEvalFuncPtr.h"
    "/home/bruno/paradiseo/eo/src/eoEvalKeepBest.h"
    "/home/bruno/paradiseo/eo/src/eoEvalNamedPipe.h"
    "/home/bruno/paradiseo/eo/src/eoEvalNanThrowException.h"
    "/home/bruno/paradiseo/eo/src/eoEvalPrint.h"
    "/home/bruno/paradiseo/eo/src/eoEvalTimeThrowException.h"
    "/home/bruno/paradiseo/eo/src/eoEvalUserTimeThrowException.h"
    "/home/bruno/paradiseo/eo/src/eoExceptions.h"
    "/home/bruno/paradiseo/eo/src/eoExtendedVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoFactory.h"
    "/home/bruno/paradiseo/eo/src/eoFastGA.h"
    "/home/bruno/paradiseo/eo/src/eoFitContinue.h"
    "/home/bruno/paradiseo/eo/src/eoFitnessScalingSelect.h"
    "/home/bruno/paradiseo/eo/src/eoFixedInertiaWeightedVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoFlOrBinOp.h"
    "/home/bruno/paradiseo/eo/src/eoFlOrMonOp.h"
    "/home/bruno/paradiseo/eo/src/eoFlOrQuadOp.h"
    "/home/bruno/paradiseo/eo/src/eoFlight.h"
    "/home/bruno/paradiseo/eo/src/eoForge.h"
    "/home/bruno/paradiseo/eo/src/eoFunctor.h"
    "/home/bruno/paradiseo/eo/src/eoFunctorStore.h"
    "/home/bruno/paradiseo/eo/src/eoG3Replacement.h"
    "/home/bruno/paradiseo/eo/src/eoGaussRealWeightUp.h"
    "/home/bruno/paradiseo/eo/src/eoGenContinue.h"
    "/home/bruno/paradiseo/eo/src/eoGenOp.h"
    "/home/bruno/paradiseo/eo/src/eoGeneralBreeder.h"
    "/home/bruno/paradiseo/eo/src/eoInit.h"
    "/home/bruno/paradiseo/eo/src/eoInitializer.h"
    "/home/bruno/paradiseo/eo/src/eoInt.h"
    "/home/bruno/paradiseo/eo/src/eoIntegerVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoInvalidateOps.h"
    "/home/bruno/paradiseo/eo/src/eoInvertedContinue.h"
    "/home/bruno/paradiseo/eo/src/eoLinearDecreasingWeightUp.h"
    "/home/bruno/paradiseo/eo/src/eoLinearFitScaling.h"
    "/home/bruno/paradiseo/eo/src/eoLinearTopology.h"
    "/home/bruno/paradiseo/eo/src/eoMGGReplacement.h"
    "/home/bruno/paradiseo/eo/src/eoMerge.h"
    "/home/bruno/paradiseo/eo/src/eoMergeReduce.h"
    "/home/bruno/paradiseo/eo/src/eoNDSorting.h"
    "/home/bruno/paradiseo/eo/src/eoNeighborhood.h"
    "/home/bruno/paradiseo/eo/src/eoObject.h"
    "/home/bruno/paradiseo/eo/src/eoOneToOneBreeder.h"
    "/home/bruno/paradiseo/eo/src/eoOp.h"
    "/home/bruno/paradiseo/eo/src/eoOpContainer.h"
    "/home/bruno/paradiseo/eo/src/eoOpSelMason.h"
    "/home/bruno/paradiseo/eo/src/eoOrderXover.h"
    "/home/bruno/paradiseo/eo/src/eoPSO.h"
    "/home/bruno/paradiseo/eo/src/eoPartiallyMappedXover.h"
    "/home/bruno/paradiseo/eo/src/eoParticleBestInit.h"
    "/home/bruno/paradiseo/eo/src/eoParticleFullInitializer.h"
    "/home/bruno/paradiseo/eo/src/eoPerf2Worth.h"
    "/home/bruno/paradiseo/eo/src/eoPeriodicContinue.h"
    "/home/bruno/paradiseo/eo/src/eoPersistent.h"
    "/home/bruno/paradiseo/eo/src/eoPop.h"
    "/home/bruno/paradiseo/eo/src/eoPopEvalFunc.h"
    "/home/bruno/paradiseo/eo/src/eoPopulator.h"
    "/home/bruno/paradiseo/eo/src/eoPrintable.h"
    "/home/bruno/paradiseo/eo/src/eoPropGAGenOp.h"
    "/home/bruno/paradiseo/eo/src/eoProportionalCombinedOp.h"
    "/home/bruno/paradiseo/eo/src/eoProportionalSelect.h"
    "/home/bruno/paradiseo/eo/src/eoRandomRealWeightUp.h"
    "/home/bruno/paradiseo/eo/src/eoRandomSelect.h"
    "/home/bruno/paradiseo/eo/src/eoRankMuSelect.h"
    "/home/bruno/paradiseo/eo/src/eoRanking.h"
    "/home/bruno/paradiseo/eo/src/eoRankingSelect.h"
    "/home/bruno/paradiseo/eo/src/eoRealBoundModifier.h"
    "/home/bruno/paradiseo/eo/src/eoRealParticle.h"
    "/home/bruno/paradiseo/eo/src/eoReduce.h"
    "/home/bruno/paradiseo/eo/src/eoReduceMerge.h"
    "/home/bruno/paradiseo/eo/src/eoReduceMergeReduce.h"
    "/home/bruno/paradiseo/eo/src/eoReduceSplit.h"
    "/home/bruno/paradiseo/eo/src/eoReplacement.h"
    "/home/bruno/paradiseo/eo/src/eoRingTopology.h"
    "/home/bruno/paradiseo/eo/src/eoSGA.h"
    "/home/bruno/paradiseo/eo/src/eoSGAGenOp.h"
    "/home/bruno/paradiseo/eo/src/eoSGATransform.h"
    "/home/bruno/paradiseo/eo/src/eoSIGContinue.h"
    "/home/bruno/paradiseo/eo/src/eoSTLFunctor.h"
    "/home/bruno/paradiseo/eo/src/eoScalarFitness.h"
    "/home/bruno/paradiseo/eo/src/eoScalarFitnessAssembled.h"
    "/home/bruno/paradiseo/eo/src/eoSecondsElapsedContinue.h"
    "/home/bruno/paradiseo/eo/src/eoSelect.h"
    "/home/bruno/paradiseo/eo/src/eoSelectFactory.h"
    "/home/bruno/paradiseo/eo/src/eoSelectFromWorth.h"
    "/home/bruno/paradiseo/eo/src/eoSelectMany.h"
    "/home/bruno/paradiseo/eo/src/eoSelectNumber.h"
    "/home/bruno/paradiseo/eo/src/eoSelectOne.h"
    "/home/bruno/paradiseo/eo/src/eoSelectPerc.h"
    "/home/bruno/paradiseo/eo/src/eoSequentialSelect.h"
    "/home/bruno/paradiseo/eo/src/eoSharing.h"
    "/home/bruno/paradiseo/eo/src/eoSharingSelect.h"
    "/home/bruno/paradiseo/eo/src/eoShiftMutation.h"
    "/home/bruno/paradiseo/eo/src/eoSigBinaryFlight.h"
    "/home/bruno/paradiseo/eo/src/eoSimpleEDA.h"
    "/home/bruno/paradiseo/eo/src/eoSocialNeighborhood.h"
    "/home/bruno/paradiseo/eo/src/eoStandardFlight.h"
    "/home/bruno/paradiseo/eo/src/eoStandardVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoStarTopology.h"
    "/home/bruno/paradiseo/eo/src/eoSteadyFitContinue.h"
    "/home/bruno/paradiseo/eo/src/eoStochTournamentSelect.h"
    "/home/bruno/paradiseo/eo/src/eoStochasticUniversalSelect.h"
    "/home/bruno/paradiseo/eo/src/eoSurviveAndDie.h"
    "/home/bruno/paradiseo/eo/src/eoSwapMutation.h"
    "/home/bruno/paradiseo/eo/src/eoSyncEasyPSO.h"
    "/home/bruno/paradiseo/eo/src/eoTimeContinue.h"
    "/home/bruno/paradiseo/eo/src/eoTopology.h"
    "/home/bruno/paradiseo/eo/src/eoTransform.h"
    "/home/bruno/paradiseo/eo/src/eoTruncSelect.h"
    "/home/bruno/paradiseo/eo/src/eoTruncatedSelectMany.h"
    "/home/bruno/paradiseo/eo/src/eoTruncatedSelectOne.h"
    "/home/bruno/paradiseo/eo/src/eoTwoOptMutation.h"
    "/home/bruno/paradiseo/eo/src/eoVariableInertiaWeightedVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoVariableLengthCrossover.h"
    "/home/bruno/paradiseo/eo/src/eoVariableLengthMutation.h"
    "/home/bruno/paradiseo/eo/src/eoVector.h"
    "/home/bruno/paradiseo/eo/src/eoVectorParticle.h"
    "/home/bruno/paradiseo/eo/src/eoVelocity.h"
    "/home/bruno/paradiseo/eo/src/eoVelocityInit.h"
    "/home/bruno/paradiseo/eo/src/eoWeightUpdater.h"
    "/home/bruno/paradiseo/eo/src/es.h"
    "/home/bruno/paradiseo/eo/src/ga.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/paradiseo/eo" TYPE DIRECTORY FILES
    "/home/bruno/paradiseo/eo/src/do"
    "/home/bruno/paradiseo/eo/src/es"
    "/home/bruno/paradiseo/eo/src/ga"
    "/home/bruno/paradiseo/eo/src/gp"
    "/home/bruno/paradiseo/eo/src/other"
    "/home/bruno/paradiseo/eo/src/utils"
    FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/checkpointing$" REGEX "/external\\_eo$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/bruno/paradiseo/build/eo/src/es/cmake_install.cmake")
  include("/home/bruno/paradiseo/build/eo/src/ga/cmake_install.cmake")
  include("/home/bruno/paradiseo/build/eo/src/utils/cmake_install.cmake")

endif()

