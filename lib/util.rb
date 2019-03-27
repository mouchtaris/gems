require 'pathname'
module Util
  module_function

  def load_yaml(source)
    case source
    when ::Pathname
      source.open('r') { |fin| load_yaml(fin) }
    when ::String
      File.open('r', source) { |fin| load_yaml(fin) }
    when ::IO
      YAML.safe_load(source)
    else
      raise ArgumentError, "Cannot handle #{source.inspect} as a YAML source"
    end
  end
end
