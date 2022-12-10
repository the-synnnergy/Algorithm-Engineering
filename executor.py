from distutils.command.config import config
import subprocess
import os


rootdir = "Instances"
population = ["50","100","150","200"]
mut_rate = ["0.05","0.1","0.15"]
generations = ["100","500","1000","1500"]
configs = list()
for pop in population:
    for mut in mut_rate:
        for gen in generations:
            tmp_config = list()
            tmp_config.append(pop)
            tmp_config.append(mut)
            tmp_config.append(gen)
            configs.append(tmp_config)
for config in configs:
    solutions_dir = "solutions" +"_pop_" + config[0] + "_mut_" +config[1] + "_gen_" +config[2] 
    if(not os.path.isdir(solutions_dir)):
        os.mkdir(solutions_dir)
    for subdir, dirs, files in os.walk(rootdir):
        for file in files:
            subdir_correct = subdir.split("/")[1]
            if(not os.path.isdir(os.path.join(solutions_dir,subdir_correct))):
                os.mkdir(os.path.join(solutions_dir,subdir_correct))
            command = "./solver -in " + os.path.join(subdir,file)+ " -out " + os.path.join(solutions_dir+"/"+subdir_correct,file)+ " -alg gen"
            command = command.split()
            command.extend(config)
            print(command) 
            process = subprocess.Popen(command)
            process.wait()
            print(subdir_correct)


