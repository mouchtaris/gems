require 'args/version'

module Args
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
      @value.tap(&check(@name, Array))
      @value.each_with_index do |element, index|
        name = "#{@name}-#{index}"
        element.tap(&check(name, @check.first))
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

  Checks = [
    IsNotType,
    IsNotArrayOf,
    IsNotStructOf,
  ].freeze

  def check(name, check)
    -> (value) {
      Checks.each do |c|
        c
          .optionally_create(name, value, check)
          &.check_or_raise!
      end
    }
  end

  def get(params, name, check)
    params[name.to_s]
      .tap(&check(name, check))
  end
end
