require 'args/version'

module Args
  class Error < ArgumentError
  end

  class Check < Error
    class << self
      alias_method :can_be_from?, :===
      def optionally_create(name, value, check)
        return unless can_be_from? value
        new(name, value, check)
      end
    end

    def check_or_raise!
      check_value || (raise self)
    end

    def initialize(name, value, check)
      @name = name
      @value = value
      @check = check
      msg = "#{error_message}\n#{value.inspect}"
      super(msg)
    end
  end

  class IsNotType < Check
    def self.can_be_from?(arg)
      arg.is_a? Module
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

  Checks = [
    IsNotType
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
