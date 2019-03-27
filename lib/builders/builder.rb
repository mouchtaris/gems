module Builders
  class Builder
    extend Base

    class << self
      def handle?(scroll: nil, builder: nil)
        r0 = scroll
          &.builders_pure
          &.find { |bd| handle? builder: bd }
        r1 = builder
          &.[]('type')
          &.==(self::TYPE)
        (r0 || r0 == nil) && (r1 || r1 == nil)
      end
    end

    def initialize(scroll)
      @scroll = scroll
    end

    def handle?(**args)
      self.class.handle?(**args)
    end
  end
end
