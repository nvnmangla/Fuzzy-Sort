#include "utils.hpp"

int main(int argc, char **argv) {
  auto fnames = vector<string>{"small_overlap","all_overlap"};
  for (string file:fnames){
    vector<double> timings_{};
    vector<int>num{};

    for (int i{1};i<1000;i++){
        auto n = 10*i;
        num.push_back(n);
        auto data_ = read_file("../data/" + file + ".txt",n);
        int data_size = (int)data_.size();
        auto start = high_resolution_clock::now();
        fuzzy_sort(data_, 0, data_size - 1);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        timings_.push_back(duration.count());
    }
    
    plt::named_plot(file+".txt",num,timings_);
  }

  plt::title("Standard usage"); // set a title
  plt::legend(); 
  plt::save("../results/graph.png");
  
  return 0;
}
