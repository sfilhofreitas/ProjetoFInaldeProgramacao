# File config.txt:
	* Output path: Output directory to be created. (Only the last folder in the directory will be created)
	* Teachers: Teachers that will be used in the test with its respective parameters
	* Learners: Learners that will be used with its parameters
	* Hyptheses generator: Hyptheses Generator that will be used with its parameters
	* Number of examples: Number of examples of the synthetic dataset
	* Number of hypotheses: Learner hypotheses class size
	* Number of teacher seeds: Number of times the test will be performed modifying only the teacher's seed
	* Number of learner seeds: Number of times the test will be performed modifying only the learner's seed


# Teachers:
	* Implementations are currently completed for the teachers WeightsTheoreticalFounded and PacTeacher.
	* Each parameter must be separated by space.
	* Each teacher must be separated by a comma.

## WeightsTheoreticalFounded
	Each example has a weight that starts with 1 / 2m, where m is the size of the dataset. The value of n (estimate of the number of hypotheses) determines the maximum number of examples that can be sent to the learner in a single iteration. The teacher initially assumes that n is 1. Each example whose current learner classifies wrong has its weight updated (increased). Whenever the algorithm fails, the weights are reset and the n value is doubled. The probability of an example to be chosen is directly proportional to how much it varies in the current iteration.

	Usage syntax: WeightsTheoreticalFounded


## PacTeacher
	In each round an example is chosen at random and uniformly, disregarding the iteration with the learner.

	* Usage syntax: PacTeacher

# Learners:
	* RandomLearner and AdversaryLearner.
	* Each learner must be separated by a comma.
	

## RandomLearner
	The learner randomly (uniformly) chooses a hypothesis that is not covered by the set of examples received. The perfect hypothesis is only returned when all others are covered.

	* Usage syntax: RandomLearner

## AdversaryLearner
	The learner chooses the hypothesis of worse accuracy that is not covered by the set of examples received. Hence, the perfect hypothesis is only returned when all others are covered.

	* Usage syntax: AdversaryLearner


# Hyptheses Generator
	* Currently, the unique generator is SimpleRandomHypotheses.
	* List values are separated by '_' and without spaces as: v1_v2 _..._ v_n.

## SimpleRandomHypotheses
	A set of hypotheses (without repetitions) is generated randomly following the specified parameters.

	* Usage syntax: SimpleRandomHypotheses p1 p2 p3 p4 p5
		* p1: Accuracy list of the hyphoteses
		* p2: Fraction of examples that are more hard
		* p3: Fraction of hard examples that appear in each hypothesis. If p is 0.3, 30% of the examples that each hypothesis misses are of the set of set of hard examples and 70% of the other examples
		* p4: Number of hypothesis sets generated for the previously defined parameters



# Run:
	The code was developed on Ubuntu 18.04.3 LTS using Qt Creator IDE (QMake version 3.1 Using Qt version 5.9.7) and can be loaded in the same tool using the .pro file in the src folder.

	* Run ./Framework (src folder)

	* Run ./Framework config_path

	* Run ./Framework --tests (execute unitary tests)


# Instance of config.txt:
	OUTPUT PATH: ../Tests/output_name
	TEACHERS: WeightsTheoreticalFounded, PacTeacher
	LEARNERS: RandomLearner
	HYPOTHESES GENERATOR: SimpleRandomHypotheses 0.9 0 0 5
	NUMBER OF EXAMPLES: 12500
	NUMBER OF HYPOTHESES: 30000
	TEACHER REPETITIONS: 10
	LEARNER REPETITIONS: 10