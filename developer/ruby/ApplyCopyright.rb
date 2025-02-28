# Inserts copyright at beginning of each
#
# Inputs:
#   ARGV[0] - path to top level cmake source directory (one level above 'src' directory)

require 'pathname'
require 'rubygems'
require 'fileutils'

include FileUtils

# check that called from command line directly
if not ($0 == __FILE__)
  puts "#{__FILE__} called from external script"
  exit
end

basepath = ARGV[0].gsub("\\", "/")

copyright = "/***********************************************************************************************************************\n"
ruby_copyright = "########################################################################################################################\n"
File.open(basepath + "/../LICENSE.md") do |file|
  while (line = file.gets)
    if line.strip.empty?
      copyright +=  "*" + line
      ruby_copyright += "#" + line
    
    else
      copyright += "*  " + line
      ruby_copyright += "#  " + line
    end
  end
end
copyright += "***********************************************************************************************************************/\n\n"
ruby_copyright += "########################################################################################################################\n\n"

# first do c++

# exceptions are files that are not part of OpenStudio
exceptions = [basepath + "/src/geographic_lib/",
              basepath + "/src/google_test/",
              basepath + "/src/install_utility/",
              basepath + "/src/jsoncpp/",
              basepath + "/src/nano/",
              basepath + "/src/polypartition/",
              basepath + "/src/qtwinmigrate/",
              basepath + "/src/qwt/",    
              basepath + "/src/sqlite/",       
              basepath + "/src/zlib/",              
              basepath + "/src/utilities/sql/Sqlite3.c",
              basepath + "/src/utilities/sql/Sqlite3.h",
              "mainpage.hpp"]

# glob for hpp and cpp
files = Dir.glob(basepath + "/src/**/*.[ch]pp")

# reject exceptions
files.reject! do |p|
  result = false
  exceptions.each do |e|
    if p.include?(e)
      result = true
      puts p
      break
    end
  end
  result
end

# loop over all files
files.each do |p|

  # start with copyright
  text = copyright

  # read file
  File.open(p, "r") do |file|
    # read until end of current copyright
    while (line = file.gets)
      if not /^\s?[\/\*]/.match(line)
        if not line.chomp.empty?
          text += line
        end
        break
      end
    end

    # now keep rest of file
    while (line = file.gets)
      text += line
    end
  end

  # write file
  File.open(p, "w") do |file|
    file << text
  end

end

# now do ruby

# exceptions are files that are not part of OpenStudio
exceptions = []

# glob for hpp and cpp
files = Dir.glob(basepath + "/ruby/**/*.rb")

# reject exceptions
files.reject! do |p|
  result = false
  exceptions.each do |e|
    if p.include?(e)
      result = true
      break
    end
  end
  result
end

# loop over all files
files.each do |p|

  # start with copyright
  text = ruby_copyright

  # read file
  File.open(p, "r") do |file|
    # read until end of current copyright
    while (line = file.gets)
      if not /^#/.match(line)
        if not line.chomp.empty?
          text += line
        end
        break
      end
    end

    # now keep rest of file
    while (line = file.gets)
      text += line
    end
  end

  # write file
  File.open(p, "w") do |file|
    file << text
  end

end