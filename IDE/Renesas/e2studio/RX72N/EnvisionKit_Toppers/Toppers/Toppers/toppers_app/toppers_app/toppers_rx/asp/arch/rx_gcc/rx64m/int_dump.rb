fname = ARGV[0]
if fname then
  File.open(fname) {|file|
    file.each_line{ |int_str|
      strip_str = int_str.strip
      unless strip_str.empty? then
        int_node = strip_str.split(' ')
        puts "#define INT_#{int_node[0]} #{int_node[1]}"
      end
    }
  }
end

