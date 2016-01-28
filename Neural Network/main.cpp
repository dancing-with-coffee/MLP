#include "mlp.hpp"

using namespace std;

int main( void) {

	vector<int> neurons;
	neurons.push_back( 28 * 28);
	neurons.push_back( 256);
	neurons.push_back( 10);
	cMLP mlp( neurons);

	vector< datum> train_data, test_data;

	int train_data_size = 60000;
	int test_data_size = 10000;
	
	getMNIST( "../../MNIST DB", train_data, train_data_size, test_data, test_data_size);
	std::for_each( train_data.begin(), train_data.end(), [] ( datum& val1) { 
		std::for_each( val1.x.begin(), val1.x.end(), [] ( double& val2) {
			val2 /= 255.; 
		});
	});

	std::random_shuffle( train_data.begin(), train_data.end());
	
	//mlp.loadModel( "model");
	mlp.train( train_data, 20000, 0.01, 100);

	double result;

	std::vector<int> pred_label = mlp.predict(test_data);
	result = calcMNIST_test_error(test_data, pred_label);

	printf("Matching Rate : %.2f\n", result);

	return 0;
}