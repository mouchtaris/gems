require 'args/version'

module Args
  extend self

  class Schematic
    include Args

    def initialize(**params)
      SCHEMA.each do |name, chk|
        value = (params[name] || params[name.to_sym])
          .tap(&check(name, chk))
        instance_variable_set(:"@#{name}", value)
        self.class.class_exec do
          attr_reader name
        end
      end
    end
  end

  module ClassDecorations
    def check(name = self.name)
      Args.check(name, self)
    end
  end

  class << self
    def or(*checks)
      Or.new(checks)
    end

    def included(by_this_guy)
      class << by_this_guy
        include ClassDecorations
      end
    end
  end

  class Error < ArgumentError
    attr_reader :cause
    def initialize(msg: nil, cause: nil)
      super(msg)
      @cause = cause
    end
  end

  class Check
    class << self
      alias_method :can_be_from?, :===
      def optionally_create(name, value, check)
        return unless can_be_from? check
        new(name, value, check)
      end
    end

    def raise_error!(cause: nil)
      raise Error.new(msg: error_message, cause: cause)
    end

    def check_or_raise!
      check_value || raise_error!
    rescue ArgumentError => e
      raise_error! cause: e
    end

    def initialize(name, value, check)
      @name = name
      @value = value
      @check = check
      #msg = "#{error_message}\n#{value.inspect}"
      super()#(msg)
    end
  end

  class IsNotType < Check
    def self.can_be_from?(check)
      check.is_a? Module
    end

    def check_value
      @value.is_a? @check
    end

    def error_message
      clazz = @value.class
      ancestors = clazz.ancestors.join(', ')
      "#{@name}:#{clazz}[#{ancestors}] !>= [#{@check}]"
    end
  end

  class IsNotArrayOf < Check
    include Args

    def self.can_be_from?(check)
      check.is_a? Array
    end

    def check_value
      @value.respond_to?(:each) && @value
        .to_enum
        .each_slice(@check.size)
        .each_with_index
        .reduce(true) do |slice_accum, slice_pair|
          next unless slice_accum
          slice, slice_index = slice_pair

          slice.each_with_index.reduce(true) do |accum, element_pair|
            next unless accum
            element, index = element_pair

            name = "#{@name}[#{slice_index}:#{index}]"
            element.tap(&check(name, @check[index]))
          end
        end
    end

    def error_message
      "#{@name} !=~ (Array) #{@check}"
    end
  end

  class IsNotStructOf < Check
    include Args

    def self.can_be_from?(check)
      check.is_a? Hash
    end

    def check_value
      @value.tap(&check(@name, Hash))
      @check.each do |key, subcheck|
        name = "#{@name}/#{key}"
        value = @value[key] || @value[key.to_s]
        value.tap(&check(name, subcheck))
      end
    end

    def error_message
      "#{@name} !=~ (Hash) #{@check}"
    end
  end

  Or = Struct.new(:checks)

  class OrCheck < Check
    include Args

    def self.can_be_from?(check)
      check.is_a? Or
    end

    def safe_check_with(check)
      @value.tap(&check(@name, check))
      nil
    rescue ArgumentError => e
      e
    end

    def check_value
      @check
        .checks
        .map(&method(:safe_check_with))
        .any?(&:nil?) ||
        raise_error!
    end

    def error_message
      "All checks failed for #{@name}:\n- #{@check.checks.join("\n- ")}"
    end
  end

  Checks = [
    IsNotType,
    IsNotArrayOf,
    IsNotStructOf,
    OrCheck,
  ].freeze

  def check(name, check)
    -> (value) {
      Checks.to_enum.reduce(nil) do |accum, chk|
        accum ||
          chk.optionally_create(name, value, check)&.tap(&:check_or_raise!)
      end || (raise "No check found for #{value.inspect}")
    }
  end

  def get(params, name, check)
    params[name.to_s]
      .tap(&check(name, check))
  end
end
