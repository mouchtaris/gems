# frozen_string_literal: true

require 'spec_helper'
require 'util/class_decorations'

RSpec.describe Util::ClassDecorations do
  let(:victim) do
    dc = described_class
    Class.new do
      extend dc

      # It's to :reek:UtilityFunction
      def f_impl(x)
        x + 1
      end

      func def f(x)
        f_impl x
      end
    end
  end

  it 'can be extended' do
    expect { victim }.not_to raise_error
  end

  describe 'func decorator' do
    subject(:instance) { victim.new }

    it 'allows methods to be called argless and return a proc' do
      expect(instance.f.call(12)).to eq instance.f_impl(12)
    end

    it 'propagates arguments each time' do
      expect(instance.f.call(12)).to eq instance.f_impl(12)
      expect(instance.f.call(13)).to eq instance.f_impl(13)
    end
  end
end
