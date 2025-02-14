#/!bin/sh

perf_file=$(realpath $1)
rg "H264 perfermance test Pass" $perf_file | awk -F ',' 'NR%2==1 {print $2}' | xargs -I {} echo -n "{}, " ; echo
rg "H265 perfermance test Pass" $perf_file | awk -F ',' 'NR%2==1 {print $2}' | xargs -I {} echo -n "{}, " ; echo
rg "JPEG perfermance test Pass" $perf_file | awk -F ',' 'NR%2==1 {print $2}' | xargs -I {} echo -n "{}, " ; echo
rg "H264 perfermance test Pass" $perf_file | awk -F ',' 'NR%2==0 {print $2}' | xargs -I {} echo -n "{}, " ; echo
rg "H265 perfermance test Pass" $perf_file | awk -F ',' 'NR%2==0 {print $2}' | xargs -I {} echo -n "{}, " ; echo
rg "JPEG perfermance test Pass" $perf_file | awk -F ',' 'NR%2==0 {print $2}' | xargs -I {} echo -n "{}, " ; echo