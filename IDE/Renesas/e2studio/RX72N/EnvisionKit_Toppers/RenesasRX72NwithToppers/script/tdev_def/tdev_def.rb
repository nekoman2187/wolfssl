##########################################
# Copyright (c) 2015- Hisashi Hata       #
# Released under the toppers license     #
# https://www.toppers.jp/license.html    #
##########################################
require 'yaml'

USE_DEVICE_FILE = "use_device"
DEVICE_ID_FILE = "target_device_id"
DEVICE_NODE_FILE = "target_device_node"

NUM_OF_DEVICE = "NUM_TARGET_DEVICE"

ID_KEY = "id"
NUM_DEV_KEY = "num_dev"
HEADER_KEY = "header"
INIT_FUNC_KEY = "init_func"
NODE_TYPE_KEY = "node_type"
NODE_OBJ_KEY = "node_obj"

USE_DEFAULT = ""

LICENSE_HEADER_TXT =<<"LICENSE_EOS"
/*
 * Copyright (c) 2015- Hisashi Hata       
 * Released under the toppers license     
 * https://www.toppers.jp/license.html    
 */
LICENSE_EOS

def use_dev_str(dev_id, index)
  "USE_#{dev_id}_#{index}"
end

def dev_id_str(dev_id, index)
  "DEV_#{dev_id}#{index}"
end

def node_obj_str(node_obj, index)
  "#{node_obj}_#{index}"
end

def dev_info_str(node_obj)
  "{0x0, &#{node_obj}}"
end

def init_func_str(init_func, index)
  "#{init_func}_#{index}"
end

def if_def_code(dev_id, index, w_str)
  "#ifdef #{use_dev_str(dev_id, index)}\n  #{w_str}\n#endif\n"
end

#make use_device.h
def generate_use_device(dev_def)
  wr_str = []
  wr_str << "#{LICENSE_HEADER_TXT}\n"
  wr_str << "#ifndef TARGET_#{USE_DEVICE_FILE.upcase}_H\n"
  wr_str << "#define TARGET_#{USE_DEVICE_FILE.upcase}_H\n\n"
  
  dev_def.each{|dev_i|
    dev_i[NUM_DEV_KEY].times{|i|
      wr_str << "#{USE_DEFAULT}#define #{use_dev_str(dev_i[ID_KEY], i)}\n"
    }
  }
  
  wr_str << "\n#endif\n"
  fw = open("#{USE_DEVICE_FILE}.h", "w")
  fw.write(wr_str.join)
  fw.close
end

#make target_device_id.h
def generate_device_id(dev_def)
  wr_str = []  
  wr_str << "#{LICENSE_HEADER_TXT}\n"

  wr_str << "#ifndef TARGET_#{DEVICE_ID_FILE.upcase}_H\n"
  wr_str << "#define TARGET_#{DEVICE_ID_FILE.upcase}_H\n\n"
  #gererate include code
  wr_str << "#include \"#{USE_DEVICE_FILE}.h\"\n"
  wr_str << "\n"
  
  #generate id code
  wr_str << "typedef enum use_device_id{\n"
  wr_str << "  DEV_NULL,\n"
  dev_def.each{|dev_i|
    dev_i[NUM_DEV_KEY].times{|i|
      dev_id = "#{dev_id_str(dev_i[ID_KEY], i)},"
      wr_str << if_def_code(dev_i[ID_KEY], i, dev_id)
    }
  }
  wr_str << "  #{NUM_OF_DEVICE}\n}dnode_id;\n\n"
  wr_str << "#endif\n"
  
  fw = open("#{DEVICE_ID_FILE}.h", "w")
  fw.write(wr_str.join)
  fw.close
end

#make target_device_node.c
def generate_device_node(dev_def)
  wr_str = []  
  wr_str << "#{LICENSE_HEADER_TXT}\n"

  #gererate include code
  wr_str << "#include <kernel.h>\n"
  wr_str << "#include <target_device/target_device.h>\n"
  wr_str << "\n"
  
  #generate extern node obj code
  dev_def.each{|dev_i|
    dev_i[NUM_DEV_KEY].times{|i|
      ext_obj = "extern dev_node_t #{node_obj_str(dev_i[NODE_OBJ_KEY], i)};\n  void #{init_func_str(dev_i[INIT_FUNC_KEY], i)}();"
      wr_str << if_def_code(dev_i[ID_KEY], i, ext_obj)
    }
  }
  wr_str << "\n"
  
  #generate node code
  wr_str << "dev_info_t dev_info[#{NUM_OF_DEVICE}] = {\n"
  wr_str << "  {0x0, NULL}, //NULL DEVICE\n"
  dev_def_size = dev_def.size
  dev_def_size.times{|di|
    dev_i = dev_def[di]
    is_last_di =  (di == dev_def_size-1) ? true : false

    subdi_size = dev_i[NUM_DEV_KEY]
    dev_i[NUM_DEV_KEY].times{|i|
      if is_last_di && (i == subdi_size-1)
        separator = ""
      else
        separator = ","
      end
      node_s = "#{dev_info_str(node_obj_str(dev_i[NODE_OBJ_KEY], i))}#{separator}"
      wr_str << if_def_code(dev_i[ID_KEY], i, node_s)
    }
  }
  wr_str << "};\n"
  wr_str << "\n"
  #generate target driver init code
  wr_str << "void target_device_init(){\n"
  dev_def.each{|dev_i|
    dev_i[NUM_DEV_KEY].times{|i|
      init_func_def = "#{init_func_str(dev_i[INIT_FUNC_KEY], i)}();"
      wr_str << if_def_code(dev_i[ID_KEY], i, init_func_def)
    }
  }
  wr_str << "}\n"
    
  fw = open("#{DEVICE_NODE_FILE}.c", "w")
  fw.write(wr_str.join)
  fw.close
end
        
        

def tdev_def()
  arg_num = ARGV[0].size
  if arg_num >= 1
    devdef_file = ARGV[0]
  else
    puts "Argument Error"
    return
  end

  devdef = YAML.load_file(devdef_file)
  
  generate_use_device(devdef)
  generate_device_id(devdef)
  generate_device_node(devdef)
end
  
tdev_def()

