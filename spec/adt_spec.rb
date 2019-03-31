# frozen_string_literal: true

require 'spec_helper'

require 'adt'

RSpec.describe Adt do
  include Adt

  describe '#yaml' do
    it 'runs' do
      expect(yaml).to(
        be_a(Hash).or(
          be_an(Array)
        )
      )
    end
  end

  describe '#log' do
    it 'runs' do
      expect { log 1, lvl: 12 }.not_to raise_error
    end
  end

  describe '#parse_line' do
    it 'runs' do
      expect { parse_line(12) }.not_to raise_error
    end
  end

  describe '#parse_doc' do
    it 'needs a doc' do
      expect { parse_doc(12) }.to raise_error ParseError
    end

    it 'runs' do
      expect { parse_doc({}) }.not_to raise_error
    end
  end

  describe '#parse!' do
    it 'runs' do
      expect { parse! }.not_to raise_error
    end
  end
end
