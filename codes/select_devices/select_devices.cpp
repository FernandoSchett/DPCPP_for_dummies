#include <CL/sycl.hpp>

// creating vector sycl queue
std:: vector < sycl :: queue > qs;

void selectDevices(){
    // creating auto variables to capture the platforms
    auto platforms = sycl :: platform::get_platforms();
    bool gpu,cpu;
        gpu = cpu = false;
        // uses a loop to cycle through available platforms
        for(auto & p : platforms){
            auto name = p.get_info<sycl::info::platform::name>();
            auto devices = p.get_devices();
            // uses a loop to go through the available devices of the respective platform
            for(auto & d : devices){
                // if the device is a gpu it will be selected only once, locking the gpu variable
                if(d.is_gpu() && (!gpu)){
                    std::cout << "Platform: " << name << std::endl;
				    std::cout << " Device: " << d.get_info<sycl::info::device::name>() << std::endl;
                    qs.push_back(sycl :: queue(d));
                    gpu = true;
                }
                // if the device is a cpu it will be selected only once, locking the cpu variable
                else if(d.is_cpu() && (!cpu)){
                    std::cout << "Platform: " << name << std::endl;
				    std::cout << " Device: " << d.get_info<sycl::info::device::name>() << std::endl;
                    qs.push_back(sycl :: queue(d));
                    cpu = true;
                }
            }
        }

        // gpu and cpu were found and will be used
        if((cpu && gpu))
            std :: cout << "The algorithm will run on cpu and gpu\n";
        // only cpu will be used
        else if(cpu && !gpu){
            qs.push_back(sycl :: queue{sycl:: cpu_selector{}});
            std :: cout << "The algorithm will run on cpu\n";
        } 
        // only gpu will be used
        else if(!cpu && gpu){
            qs.push_back(sycl :: queue {sycl:: gpu_selector{}});
            std :: cout << "The algorithm will run on gpu\n";
        }
        // no device found
        else{
            std :: cout << "Devices not found\n";
            exit(1);
        }
            
}



int main(){
    selectDevices();
    return 0;
}