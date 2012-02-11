#!/usr/bin/env ruby
# --------------------  (c)john hopson  --------------------
#
#  Test suite for bringup.c program.
#
#  - Binary file lengths have no significance, unless
#    specified.  A variety of lengths are specified
#    to increase coverage.
#  - Get usage with 'bringup_test.rb -h'
#  - Requires GCC, but only basic features.
#  - Written and tested with ruby 1.8.7 on OS X 10.7.
#  - Hosted at github.com/johnhopson/bringup
#  - Licensed per creativecommons.org/licenses/by-sa/3.0


require 'test/unit'
require 'time'
require 'mathn'
require 'fileutils'


class TestBringup < Test::Unit::TestCase


  def  test_simplest_compile

    out = `gcc  -o bu.exe  ../bringup.c  2>&1`
    assert_equal 0, $?.exitstatus

    out += `./bu.exe  2>&1`
    assert_equal 0, $?.exitstatus
    assert_equal "", out
  ensure
    File.delete "bu.exe"  if File.exists? "bu.exe"
  end


  def  test_use_of_file

    `gcc  -D LOG_FILE=\\"my.log\\" -o bu.exe  ../bringup.c  2>&1`
    assert_equal 0, $?.exitstatus

    `./bu.exe  2>&1`
    assert_equal 0, $?.exitstatus

    file = File.open( "my.log", "r" ).read
    assert_equal expected_output(file), file
  ensure
    File.delete "bu.exe"  if File.exists? "bu.exe"
    File.delete "my.log"  if File.exists? "my.log"
  end


  def  test_use_of_printf
    common_test  ""
  end


  def  test_use_of_timing
    common_test  "-D MEASURE_TIME", {:addtime => true}
  end


  def  test_2_cycles
    common_test  "-D NUM_CYCLES=2", {:cycles => 2}
  end


  def  test_125_cycles
    common_test  "-D NUM_CYCLES=125", {:cycles => 125}
  end


  def  test_large_prime_candidate
    common_test  "-D MAX_PRIME_CANDIDATE=17500",
                 {:maxprime => 17500}
  end


  def  test_file_and_printf_together

    common_test  "-D LOG_FILE=\\\"my.log\\\""

    file = File.open( "my.log", "r" ).read
    assert_equal expected_output(file), file
  ensure
    File.delete "my.log"  if File.exists? "my.log"
  end


  def  test_many_params

    parms = {:maxprime => 2015,
             :cycles   => 81,
             :addtime  => true}

    common_test  "-D LOG_FILE=\\\"my.log\\\" -D MAX_PRIME_CANDIDATE=2015 " +
                 "-D NUM_CYCLES=81 -D MEASURE_TIME",
                 parms

    file = File.open( "my.log", "r" ).read
    assert_equal expected_output(file, parms), file
  ensure
    File.delete "my.log"  if File.exists? "my.log"
  end


  def  test_that_c_compile_can_fail

    #  first, be sure copy compiles
    FileUtils.copy( "../bringup.c", "temp.c" )
    out = `gcc  -o bu.exe  temp.c  2>&1`
    assert_equal 0, $?.exitstatus
    File.delete  "bu.exe"

    #  corrupt temp.c
    text = File.read( "temp.c" )
    text.gsub! /\}/, ""
    File.open( "temp.c", "w" ) { |f| f.puts text }

    #  verify compile fails
    out = `gcc  -o bu.exe  temp.c  2>&1`
    assert_not_equal 0, $?.exitstatus

  ensure
    File.delete "bu.exe"  if File.exists? "bu.exe"
    File.delete "temp.c"  if File.exists? "temp.c"
  end


  def  test_that_output_comparison_can_fail

    #  compile and run default config
    out = `gcc  -D USE_PRINTF  -o bu.exe  ../bringup.c  2>&1`
    assert_equal 0, $?.exitstatus

    out += `./bu.exe  2>&1`
    assert_equal 0, $?.exitstatus

    expected = expected_output( out )
    assert_equal  expected, out

    #  remove info from expected output
    #  and be sure it's not the same.
    assert_not_equal  expected[0..-2], out

  ensure
    File.delete "bu.exe"  if File.exists? "bu.exe"
  end



  # --  support methods  -------------------------------------

  protected


  #  Most common test scenario - generate
  #  binary file, run bin2c, check output.

  def  common_test  cmdline,
                    expected={}

    assert  File.exist?( "bu.exe" ) == false

    out = `gcc  -D USE_PRINTF  #{cmdline} -o bu.exe  ../bringup.c  2>&1`
    assert_equal 0, $?.exitstatus

    out += `./bu.exe  2>&1`
    assert_equal 0, $?.exitstatus
    assert_equal expected_output(out, expected), out

  ensure
    File.delete "bu.exe"  if File.exists? "bu.exe"
  end


  def  expected_output  compare, params={}

    maxprime=params[:maxprime] || 1000
    cycles  =params[:cycles]   || 1
    addtime =params[:addtime]  || false

    #  Just copy date from output for compare.
    #  Impossible to guarantee generated date
    #  will be the same.

    out = ""

    compare.scan( /^bringup 1.1  \(([A-Za-z]{3})\s{1,2}(\d{1,2}) (\d{4})\)/ )  do
      |month, day, year|

      out = "bringup 1.1  (%s %2s %s)\n" % [month, day, year]
    end
    assert_not_equal "", out

    cycles.times  do |i|
      out +=                                             "\n" +
             "Cycle: %d" % [i+1]                       + "\n" +
             "The primes from 2 to %d are:" % maxprime + "\n" +
             generate_primes( maxprime )
    end

    if addtime == true
      compare.scan( /^Test time: (\d+)ms/ )  do |time|
        out += "\nTest time: %dms\n\n" % time
      end
    end

    out
  end


  def  generate_primes  max
    out = ""
    primes = Prime.new

    primes.each do |prime|
      break unless prime < max
      out += "%s\n" % prime
    end

    out
  end

end
