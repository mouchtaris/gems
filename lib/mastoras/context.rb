# frozen_string_literal: true

module Mastoras
  module Context
    class Context
      def initialize
        @data = {}
        @lens_for = {}
      end

      attr_reader :data

      # :reek:MissingSafeMethod { exclude: [ bravo!, check! ] }
      class LensFor
        def initialize(ctx, name)
          @ctx = ctx
          @name = name
          @check = method :check!
        end

        def data
          @ctx.data[@name] ||= {}
        end

        def checks(default: nil)
          data['checks'] ||= default
        end

        # :reek:NilCheck
        def check!(value)
          checks&.each { |chk| chk.call value }
        end

        def check_with(chk)
          checks(default: []) << chk
        end

        def get
          data['value']
        end

        def set(value)
          data['value'] = value.tap(@check)
        end
      end

      def lens_for(name)
        @lens_for[name] ||= LensFor.new(self, name)
      end
    end

    Check = Args.check(:ctx, Context)
  end
end
