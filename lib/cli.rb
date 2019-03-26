module Cli
  module_function

  def option_parser
    @option_parser ||= ::OptParse.new.tap do |opt|
    end
  end

  def cli(args)
    require_relative 'cyr'
    params = {}
    opt = option_parser
    opt.parse(args, into: params)
    puts opt
    pp params
    pp args
  end
end

Cli.cli(ARGV) if __FILE__ == $0
