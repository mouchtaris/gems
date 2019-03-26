module Funcs
  module_function

  def load_yaml
    @load_yaml ||= (
      require 'yaml'
      YAML.method(:safe_load)
    )
  end

  def shellesc
    @shellesc ||= (
      require 'shellwords'
      Shellwords.method(:shellescape)
    )
  end

  def puts
    @puts ||= Kernel.method(:puts)
  end

  def pathname
    @pathname ||= (
      require 'pathname'
      Pathname.method(:new)
    )
  end

  def pp
    @pp ||= (
      require 'pp'
      Kernel.method(:pp)
    )
  end
end
