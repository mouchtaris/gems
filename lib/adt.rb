# frozen_string_literal: true

require 'pp'
require 'yaml'
require 'json'

ParseError = Class.new(Exception)

module Adt
  module_function

  def yaml
    YAML.safe_load File.read '/,/moof/interface.yaml'
  end

  def log(*args, lvl: 0)
    msg = format('[%<lvl>3d] %<time>s: ', lvl: lvl, time: Time.now.to_s)
    PP.pp(args, msg)
    STDERR.puts msg
  end

  def parse_line(line)
    log :parse_ling, line.to_s[0..5]
  end

  def parse_doc(doc)
    log :parse_doc
    case doc
    when Hash then doc.map {}
    else raise ParseError, "unhandlable-doc:#{doc.class}"
    end
  end

  def parse!
    @line = 0
    parse_doc yaml
  rescue ParseError => ex
    log "/tmp/lols.rb:#{@line}:#{ex}", lvl: 666
  end
end

Adt.parse! if $PROGRAM_NAME == __FILE__
