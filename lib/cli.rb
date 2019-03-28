#!/usr/bin/env ruby
require 'optparse'
require 'bundler/setup'
require_relative 'cli/options'

module Cli
  def initialize(args)
    @opts = Options.new(args)
  end

  def output(result)
    case @opts.out
    when :txt
      result.each(&method(:puts))
    when :json
      require 'json'
      puts JSON.pretty_generate(result)
    when :yaml
      require 'yaml'
      YAML.dump(result, STDOUT)
    when :erb
      puts result
    end
  end

  def help!
    puts @opts
  end

  def workspace
    @workspace ||= (
      require_relative 'workspace'
      root = Pathname.new(@opts.root || (raise "--#{Options::ROOT} required"))
      Workspace.new(root)
    )
  end

  def queries
    @queries ||= (require_relative 'cli/queries'; Queries)
  end

  def actions
    @actions ||= (require_relative 'cli/actions'; Actions)
  end

  def builders
    workspace.builders
  end

  def list!(what)
    output(what.module_keys)
  end

  def perform!(what, key, optkey)
    performable_class = what[key] || (
      raise "#{what} not found: #{key}; try -#{optkey} to list"
    )
    performable = performable_class.new(workspace)
    output(performable.perform(@opts))
  end

  def execute!
    return help! if @opts.help?
    return list! queries if @opts.list_queries?
    return list! actions if @opts.list_actions?
    return list! builders if @opts.list_builders?
    return perform! queries, @opts.query, Options::QUERY_KEY if @opts.query
    return perform! actions, @opts.action, Options::ACTION_KEY if @opts.action
    puts '???'
    pp @opts
  rescue RuntimeError => e
    pp e
    pp @opts
  end

  class << self
    def new(args)
      Class.new { include Cli }.new(args)
    end
  end
end

Cli.new(ARGV).execute! if __FILE__ == $0
