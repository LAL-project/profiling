TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17 -fPIC -fopenmp #-flto -fno-fat-lto-objects -O3
QMAKE_CXXFLAGS_DEBUG += -DDEBUG -D_GLIBCXX_DEBUG
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -UDEBUG -DNDEBUG -fstrict-aliasing

QMAKE_LFLAGS += -fPIC -O3 #-flto -fno-fat-lto-objects
QMAKE_LFLAGS_RELEASE += -DNDEBUG -UDEBUG
QMAKE_LFLAGS_DEBUG += -DDEBUG -D_GLIBCXX_DEBUG

LIBS += -lgmp -fopenmp -lpthread

# uncomment when doing actual profiling
# QMAKE_CXXFLAGS_RELEASE += -pg
# QMAKE_CXXFLAGS_RELEASE -= -O3
# QMAKE_LFLAGS += -pg

isEmpty(ENVIR) {
    ENVIR = "HOME"
}

# configure home
equals(ENVIR, "HOME") {
	LAL_DIR = /home/lluis/Documents/projects/LAL-dev/latest/linear-arrangement-library
	INCLUDEPATH += $$LAL_DIR

	# add definitions
	DEFINES += "__ENVIR=0"
}

# configure cluster
equals(ENVIR, "CLUSTER") {
    QMAKE_CXX = /home/soft/gcc-11.2.0/bin/g++
	QMAKE_LINK = /home/soft/gcc-11.2.0/bin/g++

	LAL_DIR = /home/usuaris/lalemany/LAL-dev/latest/linear-arrangement-library
	INCLUDEPATH += $$LAL_DIR

	DEFINES += "__ENVIR=1"
}

SOURCES += \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB_constraints.cpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB_execution.cpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB_execution_independent_set.cpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB_initialisation.cpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB_next_action.cpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB_state_manipulation.cpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB_utils.cpp \
	../../linear-arrangement-library/lal/generate/all_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/all_bipartite_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/all_lab_free_trees.cpp \
	../../linear-arrangement-library/lal/generate/all_planar_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/all_projective_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/all_ulab_free_trees.cpp \
	../../linear-arrangement-library/lal/generate/all_ulab_rooted_trees.cpp \
	../../linear-arrangement-library/lal/generate/rand_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/rand_bipartite_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/rand_lab_free_trees.cpp \
	../../linear-arrangement-library/lal/generate/rand_planar_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/rand_projective_arrangements.cpp \
	../../linear-arrangement-library/lal/generate/rand_ulab_free_trees.cpp \
	../../linear-arrangement-library/lal/generate/rand_ulab_rooted_trees.cpp \
	../../linear-arrangement-library/lal/graphs/conversions.cpp \
	../../linear-arrangement-library/lal/graphs/directed_graph.cpp \
	../../linear-arrangement-library/lal/graphs/free_tree.cpp \
	../../linear-arrangement-library/lal/graphs/graph.cpp \
	../../linear-arrangement-library/lal/graphs/rooted_tree.cpp \
	../../linear-arrangement-library/lal/graphs/tree.cpp \
	../../linear-arrangement-library/lal/graphs/tree_literals.cpp \
	../../linear-arrangement-library/lal/graphs/undirected_graph.cpp \
	../../linear-arrangement-library/lal/io/check_correctness.cpp \
	../../linear-arrangement-library/lal/io/edge_list.cpp \
	../../linear-arrangement-library/lal/io/head_vector.cpp \
	../../linear-arrangement-library/lal/io/treebank_collection_processor.cpp \
	../../linear-arrangement-library/lal/io/treebank_collection_reader.cpp \
	../../linear-arrangement-library/lal/io/treebank_processor.cpp \
	../../linear-arrangement-library/lal/io/treebank_reader.cpp \
	../../linear-arrangement-library/lal/linarr/C/C.cpp \
	../../linear-arrangement-library/lal/linarr/C/predict.cpp \
	../../linear-arrangement-library/lal/linarr/D/D.cpp \
	../../linear-arrangement-library/lal/linarr/D/DMax.cpp \
	../../linear-arrangement-library/lal/linarr/D/DMax_unconstrained_all.cpp \
	../../linear-arrangement-library/lal/linarr/D/Dmin.cpp \
	../../linear-arrangement-library/lal/linarr/chunking/chunking.cpp \
	../../linear-arrangement-library/lal/linarr/dependency_flux.cpp \
	../../linear-arrangement-library/lal/linarr/formal_constraints.cpp \
	../../linear-arrangement-library/lal/linarr/head_initial.cpp \
	../../linear-arrangement-library/lal/linarr/syntactic_dependency_tree/classify.cpp \
	../../linear-arrangement-library/lal/numeric/integer.cpp \
	../../linear-arrangement-library/lal/numeric/rational.cpp \
	../../linear-arrangement-library/lal/properties/C_rla.cpp \
	../../linear-arrangement-library/lal/properties/D_rla.cpp \
	../../linear-arrangement-library/lal/properties/Q.cpp \
	../../linear-arrangement-library/lal/properties/bipartite_graph_colorability.cpp \
	../../linear-arrangement-library/lal/properties/branchless_path_find.cpp \
	../../linear-arrangement-library/lal/properties/hierarchical_distance.cpp \
	../../linear-arrangement-library/lal/properties/maximum_spanning_trees.cpp \
	../../linear-arrangement-library/lal/properties/tree_centre.cpp \
	../../linear-arrangement-library/lal/properties/tree_centroid.cpp \
	../../linear-arrangement-library/lal/properties/tree_diameter.cpp \
	../../linear-arrangement-library/lal/properties/variance_C_forests.cpp \
	../../linear-arrangement-library/lal/properties/variance_C_gen_graphs.cpp \
	../../linear-arrangement-library/lal/properties/vertex_orbits.cpp \
	../../linear-arrangement-library/lal/utilities/tree_isomorphism.cpp \
    conversion.cpp \
    dir_to_undir_pp.cpp \
    generate.cpp \
    generate_arrangements_pp.cpp \
    generate_trees_pp.cpp \
    linarr_C.cpp \
    linarr_C_pp.cpp \
    linarr_Dmin.cpp \
    linarr_Dmin_pp.cpp \
	linarr_DMax.cpp \
	linarr_DMax_pp.cpp \
	main.cpp \
    properties_centroid_centre.cpp \
    properties_centroid_centre_pp.cpp \
    utilities_tree_isomorphism.cpp

HEADERS += \
	../../linear-arrangement-library/lal/C.hpp \
	../../linear-arrangement-library/lal/D.hpp \
	../../linear-arrangement-library/lal/basic_types.hpp \
	../../linear-arrangement-library/lal/detail/arrangement_wrapper.hpp \
	../../linear-arrangement-library/lal/detail/avl.hpp \
	../../linear-arrangement-library/lal/detail/data_array.hpp \
	../../linear-arrangement-library/lal/detail/generate/make_arrangement.hpp \
	../../linear-arrangement-library/lal/detail/graphs/conversions.hpp \
	../../linear-arrangement-library/lal/detail/graphs/cycles.hpp \
	../../linear-arrangement-library/lal/detail/graphs/enumerate_sets.hpp \
	../../linear-arrangement-library/lal/detail/graphs/is_tree.hpp \
	../../linear-arrangement-library/lal/detail/graphs/reachability.hpp \
	../../linear-arrangement-library/lal/detail/graphs/retrieve_subtrees.hpp \
	../../linear-arrangement-library/lal/detail/graphs/size_subtrees.hpp \
	../../linear-arrangement-library/lal/detail/graphs/traversal.hpp \
	../../linear-arrangement-library/lal/detail/graphs/tree_classification.hpp \
	../../linear-arrangement-library/lal/detail/graphs/tree_type.hpp \
	../../linear-arrangement-library/lal/detail/graphs/union_find.hpp \
	../../linear-arrangement-library/lal/detail/graphs/utils.hpp \
	../../linear-arrangement-library/lal/detail/io/check_correctness.hpp \
	../../linear-arrangement-library/lal/detail/linarr/C/brute_force.hpp \
	../../linear-arrangement-library/lal/detail/linarr/C/crossings.hpp \
	../../linear-arrangement-library/lal/detail/linarr/C/dyn_prog.hpp \
	../../linear-arrangement-library/lal/detail/linarr/C/ladder.hpp \
	../../linear-arrangement-library/lal/detail/linarr/C/predict.hpp \
	../../linear-arrangement-library/lal/detail/linarr/C/stack_based.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/D.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/1_eq_thistle_AEF.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/Bipartite_AEF.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/Planar_AEF.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/Projective_AEF.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/necessary_conditions.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/BnB.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/unconstrained/branch_and_bound/AEF/set_maximum_arrangements.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/DMax/utils.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/Bipartite_AEF.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/Planar_AEF.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/Planar_HS.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/Projective_AEF.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/Projective_HS.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/Unconstrained_FC.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/Unconstrained_YS.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dmin/utils.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/Dopt_utils.hpp \
	../../linear-arrangement-library/lal/detail/linarr/D/bipartite_opt_utils.hpp \
	../../linear-arrangement-library/lal/detail/linarr/chunking/Anderson.hpp \
	../../linear-arrangement-library/lal/detail/linarr/chunking/Macutek.hpp \
	../../linear-arrangement-library/lal/detail/linarr/dependency_flux.hpp \
	../../linear-arrangement-library/lal/detail/linarr/formal_constraints.hpp \
	../../linear-arrangement-library/lal/detail/linarr/headedness.hpp \
	../../linear-arrangement-library/lal/detail/linarr/level_signature.hpp \
	../../linear-arrangement-library/lal/detail/linarr/syntactic_dependency_tree.hpp \
	../../linear-arrangement-library/lal/detail/linear_queue.hpp \
	../../linear-arrangement-library/lal/detail/linear_set.hpp \
	../../linear-arrangement-library/lal/detail/macros/basic_convert.hpp \
	../../linear-arrangement-library/lal/detail/make_array.hpp \
	../../linear-arrangement-library/lal/detail/numeric/utils.hpp \
	../../linear-arrangement-library/lal/detail/pairs_utils.hpp \
	../../linear-arrangement-library/lal/detail/properties/bipartite_graph_colorability.hpp \
	../../linear-arrangement-library/lal/detail/properties/branchless_path_find.hpp \
	../../linear-arrangement-library/lal/detail/properties/tree_centre.hpp \
	../../linear-arrangement-library/lal/detail/properties/tree_centroid.hpp \
	../../linear-arrangement-library/lal/detail/properties/tree_diameter.hpp \
	../../linear-arrangement-library/lal/detail/properties/tree_maximum_caterpillar.hpp \
	../../linear-arrangement-library/lal/detail/sorting/bit_sort.hpp \
	../../linear-arrangement-library/lal/detail/sorting/counting_sort.hpp \
	../../linear-arrangement-library/lal/detail/sorting/insertion_sort.hpp \
	../../linear-arrangement-library/lal/detail/sorting/sorted_vector.hpp \
	../../linear-arrangement-library/lal/detail/sorting/sorting_types.hpp \
	../../linear-arrangement-library/lal/detail/type_traits/bool_sequence.hpp \
	../../linear-arrangement-library/lal/detail/type_traits/conditional_list.hpp \
	../../linear-arrangement-library/lal/detail/type_traits/first_true.hpp \
	../../linear-arrangement-library/lal/detail/type_traits/is_pointer_iterator.hpp \
	../../linear-arrangement-library/lal/detail/type_traits/ith_type.hpp \
	../../linear-arrangement-library/lal/detail/type_traits/type_sequence.hpp \
	../../linear-arrangement-library/lal/detail/utilities/tree_isomorphism.hpp \
	../../linear-arrangement-library/lal/generate.hpp \
	../../linear-arrangement-library/lal/generate/all_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/all_bipartite_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/all_lab_free_trees.hpp \
	../../linear-arrangement-library/lal/generate/all_lab_rooted_trees.hpp \
	../../linear-arrangement-library/lal/generate/all_planar_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/all_projective_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/all_ulab_free_trees.hpp \
	../../linear-arrangement-library/lal/generate/all_ulab_rooted_trees.hpp \
	../../linear-arrangement-library/lal/generate/rand_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/rand_bipartite_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/rand_lab_free_trees.hpp \
	../../linear-arrangement-library/lal/generate/rand_lab_rooted_trees.hpp \
	../../linear-arrangement-library/lal/generate/rand_planar_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/rand_projective_arrangements.hpp \
	../../linear-arrangement-library/lal/generate/rand_ulab_free_trees.hpp \
	../../linear-arrangement-library/lal/generate/rand_ulab_rooted_trees.hpp \
	../../linear-arrangement-library/lal/generate/tree_generator.hpp \
	../../linear-arrangement-library/lal/generate/tree_generator_type.hpp \
	../../linear-arrangement-library/lal/graphs.hpp \
	../../linear-arrangement-library/lal/graphs/conversions.hpp \
	../../linear-arrangement-library/lal/graphs/directed_graph.hpp \
	../../linear-arrangement-library/lal/graphs/free_tree.hpp \
	../../linear-arrangement-library/lal/graphs/graph.hpp \
	../../linear-arrangement-library/lal/graphs/output.hpp \
	../../linear-arrangement-library/lal/graphs/rooted_tree.hpp \
	../../linear-arrangement-library/lal/graphs/tree.hpp \
	../../linear-arrangement-library/lal/graphs/tree_literals.hpp \
	../../linear-arrangement-library/lal/graphs/tree_type.hpp \
	../../linear-arrangement-library/lal/graphs/undirected_graph.hpp \
	../../linear-arrangement-library/lal/io.hpp \
	../../linear-arrangement-library/lal/io/basic_output.hpp \
	../../linear-arrangement-library/lal/io/check_correctness.hpp \
	../../linear-arrangement-library/lal/io/edge_list.hpp \
	../../linear-arrangement-library/lal/io/head_vector.hpp \
	../../linear-arrangement-library/lal/io/process_treebank_base.hpp \
	../../linear-arrangement-library/lal/io/report_correctness.hpp \
	../../linear-arrangement-library/lal/io/treebank_collection_processor.hpp \
	../../linear-arrangement-library/lal/io/treebank_collection_reader.hpp \
	../../linear-arrangement-library/lal/io/treebank_error.hpp \
	../../linear-arrangement-library/lal/io/treebank_error_type.hpp \
	../../linear-arrangement-library/lal/io/treebank_feature.hpp \
	../../linear-arrangement-library/lal/io/treebank_processor.hpp \
	../../linear-arrangement-library/lal/io/treebank_reader.hpp \
	../../linear-arrangement-library/lal/iterators.hpp \
	../../linear-arrangement-library/lal/iterators/E_iterator.hpp \
	../../linear-arrangement-library/lal/iterators/Q_iterator.hpp \
	../../linear-arrangement-library/lal/lal_version.hpp \
	../../linear-arrangement-library/lal/linarr.hpp \
	../../linear-arrangement-library/lal/linarr/C/C.hpp \
	../../linear-arrangement-library/lal/linarr/C/algorithms_C.hpp \
	../../linear-arrangement-library/lal/linarr/D/D.hpp \
	../../linear-arrangement-library/lal/linarr/D/DMax.hpp \
	../../linear-arrangement-library/lal/linarr/D/Dmin.hpp \
	../../linear-arrangement-library/lal/linarr/D/algorithms_Dmin.hpp \
	../../linear-arrangement-library/lal/linarr/D/algorithms_Dmin_planar.hpp \
	../../linear-arrangement-library/lal/linarr/D/algorithms_Dmin_projective.hpp \
	../../linear-arrangement-library/lal/linarr/aggregations/1level.hpp \
	../../linear-arrangement-library/lal/linarr/aggregations/2level.hpp \
	../../linear-arrangement-library/lal/linarr/chunking/algorithms.hpp \
	../../linear-arrangement-library/lal/linarr/chunking/chunk.hpp \
	../../linear-arrangement-library/lal/linarr/chunking/chunking.hpp \
	../../linear-arrangement-library/lal/linarr/chunking/output.hpp \
	../../linear-arrangement-library/lal/linarr/dependency_flux.hpp \
	../../linear-arrangement-library/lal/linarr/formal_constraints.hpp \
	../../linear-arrangement-library/lal/linarr/head_initial.hpp \
	../../linear-arrangement-library/lal/linarr/syntactic_dependency_tree/classify.hpp \
	../../linear-arrangement-library/lal/linarr/syntactic_dependency_tree/type.hpp \
	../../linear-arrangement-library/lal/linear_arrangement.hpp \
	../../linear-arrangement-library/lal/numeric.hpp \
	../../linear-arrangement-library/lal/numeric/integer.hpp \
	../../linear-arrangement-library/lal/numeric/integer_output.hpp \
	../../linear-arrangement-library/lal/numeric/output.hpp \
	../../linear-arrangement-library/lal/numeric/rational.hpp \
	../../linear-arrangement-library/lal/numeric/rational_output.hpp \
	../../linear-arrangement-library/lal/properties.hpp \
	../../linear-arrangement-library/lal/properties/C_rla.hpp \
	../../linear-arrangement-library/lal/properties/D_rla.hpp \
	../../linear-arrangement-library/lal/properties/Q.hpp \
	../../linear-arrangement-library/lal/properties/bipartite_graph_colorability.hpp \
	../../linear-arrangement-library/lal/properties/bipartite_graph_coloring.hpp \
	../../linear-arrangement-library/lal/properties/branchless_path.hpp \
	../../linear-arrangement-library/lal/properties/branchless_path_find.hpp \
	../../linear-arrangement-library/lal/properties/degrees.hpp \
	../../linear-arrangement-library/lal/properties/hierarchical_distance.hpp \
	../../linear-arrangement-library/lal/properties/maximum_spanning_trees.hpp \
	../../linear-arrangement-library/lal/properties/tree_centre.hpp \
	../../linear-arrangement-library/lal/properties/tree_centroid.hpp \
	../../linear-arrangement-library/lal/properties/tree_diameter.hpp \
	../../linear-arrangement-library/lal/properties/vertex_orbits.hpp \
	../../linear-arrangement-library/lal/utilities.hpp \
	../../linear-arrangement-library/lal/utilities/aggregations.hpp \
	../../linear-arrangement-library/lal/utilities/tree_isomorphism.hpp \
    dir_to_undir_pp.hpp \
    generate_arrangements_pp.hpp \
    generate_trees_pp.hpp \
    linarr_C_pp.hpp \
    linarr_Dmin_pp.hpp \
	linarr_DMax_pp.hpp \
    properties_centroid_centre_pp.hpp \
    time.hpp

SUBDIRS += \
	../../linear-arrangement-library/lal/lal.pro
